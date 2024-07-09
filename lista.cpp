#include<iostream>
using namespace std;

struct No{
    int valor;
    No* prox; // vai armazenar o endereço do próximo nó (por isso um ponteiro) 

    No(){
        prox = NULL;
    }
    No(int _valor){
        valor = _valor;
        prox = NULL;
    }
};

struct Lista{
    No* inicio;
    No* fim;
    int tam;

    Lista(){
        inicio = NULL;
        fim = NULL;
        tam = 0;
    }

    void inserirInicio(int valor){
        No* novo = new No(valor);
        if(tam == 0){
            inicio = novo;
            fim = novo;
        } else{
            novo->prox = inicio;
            inicio = novo;
        }
        tam++;
    }

    void inserirFinal(int valor){
        No* novo = new No(valor);
        if(tam == 0){
            inicio = novo;
            fim = novo;
        } else{
            fim->prox = novo;
            fim = novo;
        }
        tam++;
    }

    void removerInicio(){
        if(tam == 0) return;
        if(tam == 1){
            //o operador delete vai desalocar memória alocada pelo new
            delete(inicio);
            inicio = NULL;
            fim = NULL;
            tam--;
            return;
        }
        No* aux = inicio;
        inicio = inicio->prox;
        delete(aux);
        tam--;
    }

    void removerFinal(){
        if(tam == 0) return;
        if(tam == 1){
            delete(inicio);
            inicio = NULL;
            fim = NULL;
            tam--;
            return;
        }
        //como só temos referência para a posição do próximo, precisamos procurar o elemento anterior ao último para gravar como sendo o novo último
        No* aux = inicio;
        while(aux->prox != fim){ //vai achar o penultimo
            aux = aux->prox;
        }
        delete(fim);
        fim = aux;
        fim -> prox = NULL;
        tam--;
    }

    void removerNElementos(int n){
        if(tam == 0 || n <= 0) return;
        if(n >= tam){
            No* atual = inicio;
            while(atual != NULL){
                No* aux = atual;
                atual = atual->prox;
                delete(aux);
            }
            inicio = NULL;
            fim = NULL;
            tam = 0;
            return;
        }
        int posStart = (tam - n)+1, cont = 0;
        No* atual = inicio;
        No* novoFim;
        while(atual != NULL){
            cont++;
            if(cont >= posStart){
                No* aux = atual;
                atual = atual->prox;
                delete(aux);
                continue;

            }
            //guardar o endereço do novo fim
            if(cont == posStart - 1){
                novoFim = atual;
            } 
            atual = atual->prox;
        }
        fim = novoFim;
        fim->prox = NULL;
        tam -= n;
    }

    void removerSegundoElemento(){
        if(tam <= 1) return;
        No* atual = inicio->prox;
        inicio->prox = atual->prox;
        delete(atual);
        if(tam == 2) fim = inicio;
        tam--;
    }

    void inserirTamanhoLista(){
        inserirFinal(tam);
    }

    void inserir1aN(int n){
        for(int i=1; i<=n; i++){
            inserirFinal(i);
        }
    }

    void inserirPenultimaPosicao(int valor){
        if(tam <= 1) return;
        No* atual = inicio;
        while(atual != NULL){
            if(atual->prox == fim){
                No* novo = new No(valor);
                novo->prox = fim;
                atual->prox = novo;
                break;
            }
            atual = atual->prox;
        }
    }

    void imprimir(){
        if(tam == 0) {
            cout << "Lista vazia!\n";
            return;
        }
        No* atual = inicio;
        while(atual != NULL){
            cout << atual->valor << "\n";
            atual = atual->prox;
        }
    }
};

int main(){
    Lista l;

    l.inserirInicio(10);
    l.inserirInicio(8);
    l.inserirInicio(5);
    l.inserirInicio(20);
    l.inserirFinal(76);
    l.inserirInicio(3);
    l.imprimir();
    cout << endl;
    l.removerNElementos(4);
    l.removerSegundoElemento();
    l.inserirTamanhoLista();
    l.inserir1aN(3);
    l.inserirPenultimaPosicao(89);
    l.inserirPenultimaPosicao(7);
    l.imprimir();
    return 0;
}
