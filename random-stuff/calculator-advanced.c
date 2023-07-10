#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

/*** utilities ***/
#define LOG(...) printf("[LOG]: " __VA_ARGS__)
#define ERR(...) \
    do { \
        fprintf(stderr, "\x1b[1;31m[%s(): ERROR]:\x1b[0m] \x1b[31m", __func__); \
        fprintf(stderr, __VA_ARGS__); \
        fprintf(stderr, "\x1b[0m\n"); \
    } while(0)

/*** tokens ***/
#define NO_VAL -1

typedef enum token_type {
    T_NUMBER,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_PAREN_LEFT,
    T_PAREN_RIGHT,
    T_EOF,
    TOKEN_TYPE_COUNT
} TokenType;

const char *tokenTypeStr[] = {
    "NUMBER",
    "PLUS",
    "MINUS",
    "STAR",
    "SLASH",
    "PAREN_LEFT",
    "PAREN_RIGHT",
    "EOF",
    "UNKNOWN"
};

const char *t2s(TokenType t) {
    if(t > TOKEN_TYPE_COUNT) {
        return tokenTypeStr[7];
    }
    return tokenTypeStr[t];
}


typedef struct token {
    TokenType type;
    int line;
    int value; // for number literals
} Token;

Token makeToken(TokenType type, int line, int value) {
    Token t;
    t.type = type;
    t.line = line;
    t.value = value;
    return t;
}

/*** AST ***/
typedef enum node_type {
    ND_ADD, ND_SUB,
    ND_MUL, ND_DIV,
    ND_NUM
} NodeType;

typedef struct ast_node {
    NodeType type;
    int value; // for literals
    struct ast_node *left, *right;
} ASTNode;

char nt2operator(NodeType t) {
    switch(t) {
        case ND_ADD: return '+';
        case ND_SUB: return '-';
        case ND_MUL: return '*';
        case ND_DIV: return '/';
        default:
            break;
    }
    return '?';
}


ASTNode *newASTNode(NodeType type, int value, ASTNode *left, ASTNode *right) {
    ASTNode *n = malloc(sizeof(*n));
    if(n == NULL) {
        ERR("Failed to allocate memory for a new AST node!");
        return NULL;
    }
    n->type = type;
    n->value = value;
    n->left = left;
    n->right = right;

    return n;
}

ASTNode *newASTLeaf(NodeType type, int value) {
    return newASTNode(type, value, NULL, NULL);
}

ASTNode *newASTUnary(NodeType type, int value, ASTNode *left) {
    return newASTNode(type, value, left,  NULL);
}

void freeAST(ASTNode *root) {
    if(root->left != NULL) {
        freeAST(root->left);
    }
    if(root->right != NULL) {
        freeAST(root->right);
    }
    free(root);
}

void dumpAST(ASTNode *root) {
    if(root == NULL) {
        return;
    }

    if(root->type != ND_NUM) {
        printf("%c ", nt2operator(root->type));
    } else {
        printf("%d ", root->value);
    }

    dumpAST(root->left);
    dumpAST(root->right);
}

int interpretAST(ASTNode *n) {
    if(n->type == ND_NUM) {
        return n->value;
    }

    int a = interpretAST(n->left);
    int b = interpretAST(n->right);

    switch(n->type) {
        case ND_ADD:
            return a + b;
        case ND_SUB:
            return a - b;
        case ND_MUL:
            return a * b;
        case ND_DIV:
            return a / b;
        default:
            break;
    }
    ERR("Invalid expression!");
    return 0;
}

/*** scanner ***/
typedef struct scanner {
    FILE *in;
    char current, next;
    int line;
    Token currentToken;
    bool useNext;
} Scanner;

static bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool scannerInit(Scanner *s, const char *filename) {
    s->in = fopen(filename, "r");
    if(s->in == NULL) {
        ERR("Failed to open file '%s'!", filename);
        return false;
    }
    s->current = '\0';
    s->line = 1;
    s->useNext = false;
    return true;
}
void scannerEnd(Scanner *s) {
    fclose(s->in);
    s->in = NULL;
    s->current = '\0';
    s->line = 1;
}

static char advance(Scanner *s) {
    if(feof(s->in)) {
        return '\0';
    }
    if(s->useNext) {
        s->current = s->next;
        s->useNext = false;
        return s->current;
    }
    s->current = fgetc(s->in);
    return s->current;
}
static char peek(Scanner *s) {
    return s->current;
}
static char peekNext(Scanner *s) {
    s->next = advance(s);
    s->useNext = true;
    return s->next;
}
static void skipWhiteSpace(Scanner *s) {
    char c;
    bool Continue = true;
    while(Continue) {
        c = advance(s);
        switch(c) {
            case '\t':
            case ' ':
                break;
            case '#': // comments (go until end of line)
                while(peek(s) != '\n' && !feof(s->in)) {
                    advance(s);
                }
                s->line++;
                break;
            case '\n':
                s->line++;
                break;
            case '\0':
            default:
                Continue = false;
                break;
        }
    }
}
static Token scanNumber(Scanner *s) {
    int value = peek(s) - '0';
    while(isDigit(peekNext(s))) {
        value *= 10;
        value += advance(s) - '0';
    }
    return makeToken(T_NUMBER, s->line, value);
}

Token scannerNext(Scanner *s) {
    skipWhiteSpace(s);
    Token t;
    switch(peek(s)) {
        case '+': t = makeToken(T_PLUS, s->line, NO_VAL); break;
        case '-': t = makeToken(T_MINUS, s->line, NO_VAL); break;
        case '*': t = makeToken(T_STAR, s->line, NO_VAL); break;
        case '/': t = makeToken(T_SLASH, s->line, NO_VAL); break;
        case '(': t = makeToken(T_PAREN_LEFT, s->line, NO_VAL); break;
        case ')': t = makeToken(T_PAREN_RIGHT, s->line, NO_VAL); break;
        case '\n':
            s->line++;
            break;
        case '\0':
        default:
            if(isDigit(peek(s))) {
                t = scanNumber(s);
                break;
            }
            t = makeToken(T_EOF, s->line, NO_VAL);
            break;
    }
    s->currentToken = t;
    return t;
}
Token scannerPeek(Scanner *s) {
    return s->currentToken;
}
void scannerTest() {
    Scanner s;
    if(!scannerInit(&s, "test.calc")) {
        ERR("Failed to initialize scanner!");
        return;
    }
    Token t;
    int oldline = 0;
    while((t = scannerNext(&s)).type != T_EOF) {
        if(oldline != s.line) {
            printf("%2d  ", s.line);
            oldline = s.line;
        } else {
            printf("  | ");
        }
        printf("%s", t2s(t.type));
        if(t.type == T_NUMBER) {
            printf(": %d\n", t.value);
        } else {
            printf("\n");
        }
    }
    scannerEnd(&s);
}

/*** Parser ***/
// primary -> L_PAREN expr R_PAREN | NUMBER
// factor -> primary (STAR primary | SLASH primary)*
// expr -> factor (PLUS factor | MINUS factor)*

static ASTNode *expression(Scanner *s);


static ASTNode *primary(Scanner *s) {
    Token t = scannerPeek(s);
    if(t.type == T_PAREN_LEFT) {
        scannerNext(s);
        ASTNode *n = expression(s);
        if(scannerPeek(s).type != T_PAREN_RIGHT) {
            freeAST(n);
            ERR("Expected ')'!");
            return NULL;
        }
        scannerNext(s);
        return n;
    }
    if(t.type == T_NUMBER) {
        ASTNode *n = newASTLeaf(ND_NUM, t.value);
        scannerNext(s);
        return n;
    }

    ERR("Expected expression!");
    return NULL;
}

static ASTNode *factor(Scanner *s) {
    ASTNode *node = primary(s);
    for(;;) {
        if(scannerPeek(s).type == T_STAR) {
            scannerNext(s);
            node = newASTNode(ND_MUL, 0, node, primary(s));
            continue;
        }
        if(scannerPeek(s).type == T_SLASH) {
            scannerNext(s);
            node = newASTNode(ND_DIV, 0, node, primary(s));
            continue;
        }
        break;
    }
    return node;
}

ASTNode *expression(Scanner *s) {
    ASTNode *node = factor(s);
    for(;;) {
        if(scannerPeek(s).type == T_PLUS) {
            scannerNext(s);
            node = newASTNode(ND_ADD, 0, node, factor(s));
        }
        if(scannerPeek(s).type == T_MINUS) {
            scannerNext(s);
            node = newASTNode(ND_SUB, 0, node, factor(s));
        }
        break;
    }
    return node;
}

/*** compiler ***/
// helper function to compile a file
ASTNode *compileFile(const char *path) {
    Scanner s;
    if(!scannerInit(&s, path)) {
        ERR("Failed to initialize scanner!");
        return NULL;
    }
    scannerNext(&s);
    ASTNode *n = expression(&s);
    if(n == NULL) {
        return NULL;
    }
    scannerEnd(&s);
    return n;
}

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "\x1b[1;31mInsufficient arguments provided!\n\x1b[0;1mUSAGE:\x1b[0m %s [file]\n", argv[0]);
        return 1;
    }

    ASTNode *n = compileFile(argv[1]);
    if(n == NULL) {
        return 1;
    }
    //dumpAST(n);
    //printf("\n");
    printf("result: %d\n", interpretAST(n));
    freeAST(n);
    return 0;
}