typedef struct binTree {
    int data;
    struct binTree *left;
    struct binTree *right;
    int balance;
    int level;
} BinaryTree;

void createTree(BinaryTree **t);
void createNode(BinaryTree** t, int data);
void insertTreeNodes(BinaryTree** t);
//void printTree(BinaryTree *t);
void printFormatedTree(BinaryTree *t, int xStart, int fatherY, int height);
int calcHeight(BinaryTree *t);
void calcLevel(BinaryTree **t, int level);
void calcBalance(BinaryTree **t);
//void preOrderPath(BinaryTree *t);
//void inOrderPath(BinaryTree *t);
//void visitNode(BinaryTree *t);
int searchNode(BinaryTree *t, int data);
int insertNode(BinaryTree **t, int data);
int insertAVL(BinaryTree** t, int data);
int removeNode(BinaryTree **t, int data);
int removeAVL(BinaryTree** t, int data);
void rotateLeft(BinaryTree **t);
void rotateRight(BinaryTree **t);
void balanceTree(BinaryTree **t);
void treeDifference(BinaryTree** treeA, BinaryTree* treeB);
void treeUnion(BinaryTree** treeA, BinaryTree* treeB);
void treeIntersection(BinaryTree** treeA, BinaryTree* treeB);

void createTree(BinaryTree **t) {
    *t = NULL;
}

void createNode(BinaryTree** t, int data) {
    *t = (BinaryTree*) malloc(sizeof(BinaryTree));
    (*t)->data = data;
    (*t)->left = NULL;
    (*t)->right = NULL;
    (*t)->level = 0;
    (*t)->balance = 0;
}

void insertTreeNodes(BinaryTree** t) {
    int newData = 0;
    createTree(t);
    while(newData >= 0) {
        gotoxy(1, 20);
        printf("\tEntre com o valor do novo no: ");
        scanf("%d", &newData);
        LIMPA_TELA;
        if(newData >= 0) {
            insertAVL(t, newData);
        }
        printFormatedTree(*t, 40, 0, calcHeight(*t));
        PAUSA;
    }
    LIMPA_TELA;
}

void printFormatedTree(BinaryTree *t, int xStart, int fatherY, int height) {
    if(t != NULL) {
        int rootY = fatherY + 2;
        gotoxy(xStart, rootY);
        printf("%02d", t->data);
        if(t->left != NULL) {
            int leftBarY= rootY + 1;
            gotoxy((xStart-1), leftBarY);
            printf("/");
            printFormatedTree(t->left, xStart-height-2, rootY, calcHeight(t->left));
        }
        if(t->right != NULL) {
            int rightBarY= rootY + 1;
            gotoxy((xStart+2), rightBarY);
            printf("%c", 92);
            printFormatedTree(t->right, xStart+height+2, rootY, calcHeight(t->right));
        }
        printf("\n");
    }
}

int calcHeight(BinaryTree *t) {
    if(t == NULL || (t->left == NULL && t->right == NULL)) {
        return 0;
    } else {
        if(calcHeight(t->left) > calcHeight(t->right)) {
            return 1 + calcHeight(t->left);
        } else {
            return 1 + calcHeight(t->right);
        }
    }
}

void calcLevel(BinaryTree **t, int level) {
    (*t)->level = level;
    if((*t)->left != NULL) {
        calcLevel(&(*t)->left, level + 1);
    }
    if((*t)->right != NULL) {
        calcLevel(&(*t)->right, level + 1);
    }
}

void calcBalance(BinaryTree** t) {
    int leftHeight;
    int rightHeight;
    if((*t) != NULL) {
        leftHeight = calcHeight((*t)->left);
        rightHeight = calcHeight((*t)->right);
        (*t)->balance = rightHeight - leftHeight;
        calcBalance(&(*t)->left);
        calcBalance(&(*t)->right);
    }
}

int searchNode(BinaryTree *t, int data) {
    int search;
    if(t == NULL) {
        search = 0;
    } else {
        if(t->data == data) {
            search = 1;
        } else {
            if(t->data > data) {
                if(t->left != NULL) {
                    searchNode(t->left, data);
                } else {
                    search = 2;
                }
            } else {
                if(t->right != NULL) {
                    searchNode(t->right, data);
                } else {
                    search = 3;
                }
            }
        }
    }
    return search;
}

int insertNode(BinaryTree **t, int data) {
    int search = searchNode(*t, data);
    int insertion;
    BinaryTree *aux;
    BinaryTree *auxFather = NULL;
    switch(search) {
    case 0: {
        createNode(t, data);
        insertion = 0;
        break;
    }
    case 1: {
        //printf("Dado existente!\n"); // Removido para evitar que apareca nas
        insertion = 0;                 // funcoes de Uniao, Intersecao ou Diferenca
        break;
    }
    default: {
        BinaryTree* newNode;
        createNode(&newNode, data);
        aux = *t;
        while(aux != NULL) {
            if(data < aux->data) {
                auxFather = aux;
                aux = aux->left;
            } else {
                auxFather = aux;
                aux = aux->right;
            }
        }
        if(auxFather->data < newNode->data) {
            auxFather->right = newNode;
        } else if(auxFather->data > newNode->data) {
            auxFather->left = newNode;
        }
        calcLevel(t, 0);
        calcBalance(t);
        insertion = 1;
        break;
    }
    }
    return insertion;
}

int insertAVL(BinaryTree** t, int data) {
    int insertion;
    insertion = insertNode(t, data);
    if(insertion == 1) {
        balanceTree(t);
    }
    return insertion;
}

int removeNode(BinaryTree **t, int data) {
    int search = searchNode(*t, data);
    int remotion;
    BinaryTree *aux;
    BinaryTree *auxFather = NULL;
    printf("Search: %d\n", search);
    switch(search) {
        case 0: {
            printf("\nArvore Vazia!\n");
            remotion = 0;
            break;
        }
        case 1: {
            aux = *t;
            while(aux->data != data) {
                if(data < aux->data) {
                    auxFather = aux;
                    aux = aux->left;
                } else {
                    auxFather = aux;
                    aux = aux->right;
                }
            }
            if(aux->left == NULL && aux->right == NULL) {
                if(auxFather->left == aux) {
                    auxFather->left = NULL;
                } else {
                    auxFather->right = NULL;
                }
            } else if(aux->left != NULL) {
                if(auxFather->left == aux) {
                    auxFather->left = aux->left;
                } else {
                    auxFather->right = aux->left;
                }
            } else if(aux->right != NULL) {
                if(auxFather->left == aux) {
                    auxFather->left = aux->right;
                } else {
                    auxFather->right = aux->right;
                }
            } else if(aux->left != NULL && aux->right != NULL) {
                if(auxFather->left == aux) {
                    if(aux->left->data > aux->right->data) {
                        auxFather->left = aux->left;
                    } else {
                        auxFather->left = aux->right;
                    }
                } else {
                    if(aux->left->data > aux->right->data) {
                        auxFather->right = aux->left;
                    } else {
                        auxFather->right = aux->right;
                    }
                }
            }
            free(aux);
            remotion = 1;
            calcLevel(t, 0);
            calcBalance(t);
            break;
        }
        default: {
            printf("\nElemento nao encontrado!\n");
            remotion = 0;
            break;
        }
    }
    return remotion;
}

int removeAVL(BinaryTree** t, int data) {
    int remotion;
    remotion = removeNode(t, data);
    if(remotion == 1) {
        balanceTree(t);
    }
    return remotion;
}

void rotateLeft(BinaryTree **t) {
    BinaryTree *newRoot = (*t)->right;
    BinaryTree *temp = newRoot->left;
    newRoot->left = (*t);
    (*t)->right = temp;
    (*t) = newRoot;
    calcLevel(t, 0);
}

void rotateRight(BinaryTree **t) {
    BinaryTree *newRoot = (*t)->left;
    BinaryTree *temp = newRoot->right;
    newRoot->right = (*t);
    (*t)->left = temp;
    (*t) = newRoot;
    calcLevel(t, 0);
}

void balanceTree(BinaryTree **t) {
    if((*t) != NULL) {
        if((*t)->balance <= -2 || (*t)->balance >= 2) {
            if(((*t)->left != NULL) && (((*t)->left->balance <= -2) || ((*t)->left->balance >= 2))) {
                balanceTree(&(*t)->left);
            }
            if(((*t)->right != NULL) && (((*t)->right->balance <= -2) || ((*t)->right->balance >= 2))) {
                balanceTree(&(*t)->right);
            }
            if((*t)->balance <= -2) {
                if(((*t)->left != NULL) && (*t)->left->balance > 0) {
                    rotateLeft(&(*t)->left);
                    rotateRight(t);
                } else {
                    rotateRight(t);
                }
            } else if((*t)->balance >= 2) {
                if(((*t)->right != NULL) && (*t)->right->balance < 0) {
                    rotateRight(&(*t)->right);
                    rotateLeft(t);
                } else {
                    rotateLeft(t);
                }
            }
            calcBalance(t);
        } else {
            balanceTree(&(*t)->left);
            balanceTree(&(*t)->right);
        }
    }
}

void treeDifference(BinaryTree** treeA, BinaryTree* treeB) { // Arvore A deleta os elementos que estao em A e B
    int search;
    search = searchNode(treeB, (*treeA)->data);
    if(search == 1) {
        removeAVL(&treeA, (*treeA)->data); //remove dado de A;
    }
    if((*treeA)->left != NULL) {
        treeDifference(&(*treeA)->left, treeB);
    }
    if((*treeA)->right != NULL) {
        treeDifference(&(*treeA)->right, treeB);
    }
}

void treeUnion(BinaryTree** treeA, BinaryTree* treeB) { // Arvore A recebe elementos da arvore B
    insertAVL(treeA, treeB->data);
    if(treeB->left != NULL) {
        treeUnion(treeA, treeB->left);
    }
    if(treeB->right != NULL) {
        treeUnion(treeA, treeB->right);
    }
}

void treeIntersection(BinaryTree** treeA, BinaryTree* treeB) { // Arvore A deleta os elementos dela que nao estao em B
    int search;
    search = searchNode(treeB, (*treeA)->data);
    if(search != 1) {
        removeAVL(&treeA, (*treeA)->data); //remove dado de A;
    }
    if(treeB->left != NULL) {
        treeIntersection(treeA, treeB->left);
    }
    if(treeB->right != NULL) {
        treeIntersection(treeA, treeB->right);
    }
}

// Retorna um Clone da arvore!
// Necessaria, pois ao realizar as operações de União, Interseção e Diferença
// a árvore principal T1 é modificada
// perdendo a originalidade inserida pelo usuário.

BinaryTree* getTreeClone(BinaryTree *t) { // NAO TESTADA!
	BinaryTree *clone;
	createTree(&clone);
	if(t != NULL) {
		createNode(&clone, t->data);
		clone->left = getTreeClone(t->left);
		clone->right = getTreeClone(t->right);
	}
	return clone;
}

// Funcoes nao usadas no programa
/*
void preOrderPath(BinaryTree *t) {
    if(t != NULL) {
        visitNode(t);
        preOrderPath(t->left);
        preOrderPath(t->right);
    }
}

void inOrderPath(BinaryTree *t) {
    if(t != NULL) {
        inOrderPath(t->left);
        visitNode(t);
        inOrderPath(t->right);
    }
}

void visitNode(BinaryTree *t) {
    int data = t->data;
    printf("\nDado: %2d", data);
}

void printTree(BinaryTree *t) {
    if(t != NULL) {
        int i;
        printf("%2d ", t->data);
        for(i = t->level; i >= 0; i--) {
            printf("-");
        }
        printf("\n");
        printTree(t->left);
        printTree(t->right);
    }
}
*/
