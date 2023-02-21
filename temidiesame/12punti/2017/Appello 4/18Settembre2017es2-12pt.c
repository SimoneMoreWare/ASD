#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node2 {
	char* product;
	struct node2* next;
} node2_t;

typedef struct node1 {
	char* farmer;
	struct node1* next;
	node2_t* products;
} node1_t;

node1_t* getAgricoltori();
node1_t* list_of_list_invert(node1_t *head);
void agricoltoriVisit(node1_t* agricoltori);

int main(int argc, char **argv){
	node1_t* agricoltori = getAgricoltori();
	agricoltoriVisit(agricoltori);
	printf("\n---------------------------------------------\n");
	node1_t* inverseList = list_of_list_invert(agricoltori);
	agricoltoriVisit(inverseList);
	return 420;
}

void agricoltoriVisit(node1_t* agricoltori){
	if (agricoltori == NULL) return;
	node2_t* product;
	printf("%s : ", agricoltori->farmer);
	for(product = agricoltori->products; product != NULL; product = product->next)
		printf("%s, ", product->product);
	printf("\n");
	agricoltoriVisit(agricoltori->next);
}

node1_t* newFarmer(char* farmer, node1_t* next, node2_t* products){
	node1_t* farm = malloc(sizeof(node2_t));
	farm->farmer = farmer;
	farm->next = next;
	farm->products = products;
	return farm;
}

node2_t* newProduct(char* product, node2_t* next){
	node2_t* prod = malloc(sizeof(node2_t));
	prod->next = next;
	prod->product = strdup(product);
	return prod;
}

node1_t* getAgricoltori(){
	node1_t* agricoltori = NULL;
	node2_t* prodotto = NULL;
	
	// farmer3
	
	prodotto = newProduct("product2", prodotto);
	prodotto = newProduct("product5", prodotto);
	agricoltori = newFarmer("farmer3", NULL, prodotto);
	
	prodotto = NULL;
	
	// farmer2
	
	prodotto = newProduct("product3", prodotto);
	prodotto = newProduct("product4", prodotto);
	prodotto = newProduct("product2", prodotto);
	agricoltori = newFarmer("farmer2", agricoltori, prodotto);
	
	prodotto = NULL;
	
	// farmer1
	
	prodotto = newProduct("product2", prodotto);
	prodotto = newProduct("product4", prodotto);
	prodotto = newProduct("product5", prodotto);
	agricoltori = newFarmer("farmer1", agricoltori, prodotto);
	
	return agricoltori;
	
}

node1_t* productGet(node1_t* head, char* productName){
	if (head == NULL) return NULL;
	if (strcmp(head->farmer, productName) == 0) return head;
	return productGet(head->next, productName);
}

node1_t* farmerGet(node1_t* head, char* farmerName){
	if (head == NULL) return NULL;
	if (strcmp(head->farmer, farmerName) == 0) return head;
	return farmerGet(head->next, farmerName);
}

void list_of_list_invertR(node1_t *products){
}


//Node 2 Prodotti -> Farmer
//Node 1 Farmer -> Prodotti

node1_t* list_of_list_invert(node1_t *head){
//	node2_t* farmerListToInsert;
	node1_t* productsListToReturn = NULL;
	
	node1_t* temporaryFarmer;
	node2_t* temporaryProduct;
	
	node1_t* productResearch;
	
	for(temporaryFarmer = head; temporaryFarmer != NULL; temporaryFarmer = temporaryFarmer->next){
		for(temporaryProduct = temporaryFarmer->products; temporaryProduct != NULL; temporaryProduct = temporaryProduct->next){
			productResearch = productGet(productsListToReturn, temporaryProduct->product);
			if(productResearch == NULL){
				productsListToReturn = newFarmer(temporaryProduct->product, productsListToReturn, newProduct(temporaryFarmer->farmer, NULL));
			} else {
				productResearch->products = newProduct(temporaryFarmer->farmer, productResearch->products);
			}
		}
	}
	
	return productsListToReturn;
}
