#include <iostream>
#include <exception>

#include "Pessoa.h"
using namespace std;

#include "GenericTree.h"

GenericTree::TreeNode::TreeNode(string son, int lands) {
	this->son = son;
	this->lands = lands;
	this->father = nullptr;
	this->nChild = 0;
	this->vetSize = 2;
	this->children = new GenericTree::TreeNode * [this->vetSize];
}
void GenericTree::TreeNode::addSubtree(TreeNode* n) {
	if (nChild == vetSize)
		grow();
	this->children[this->nChild] = new GenericTree::TreeNode(n->son, n->lands);
	this->children[this->nChild]->father = this;
	this->nChild++;
}
void GenericTree::TreeNode::grow() {
	GenericTree::TreeNode** aux = new GenericTree::TreeNode * [this->vetSize * 2];
	for (int i = 0; i < this->vetSize; i++)
		aux[i] = children[i];
	children = aux;
	this->vetSize *= 2;
}
bool GenericTree::TreeNode::removeSubtree(TreeNode* ref) {
	int idx = -1;
	for (int i = 0; i < this->nChild; i++) {
		if (children[i] == ref) {
			idx = i;
			break;
		}
	}
	if (idx != -1) {
		for (int i = idx + 1; i < nChild; i++) {
			children[i - 1] = children[i];
		}
		children[nChild] = nullptr;
		nChild--;
		return true;
	}
	return false;
}
GenericTree::TreeNode* GenericTree::TreeNode::getSubtree(int i) {
	if (i >= 0 && i < nChild)
		return children[i];
	return nullptr;
}
int GenericTree::TreeNode::getSubtreeSize() {
	return this->nChild;
}
GenericTree::GenericTree() {
	this->root = nullptr;
	nElements = 0;
}
GenericTree::TreeNode* GenericTree::searchNode(string son, GenericTree::TreeNode* ref) {
	if (ref != nullptr) {
		if (ref->son == son)
			return ref;
		else {
			GenericTree::TreeNode* aux;
			for (int i = 0; i < ref->getSubtreeSize(); i++) {
				aux = searchNode(son, ref->getSubtree(i));
				if (aux != nullptr)
					return aux;
			}
		}
	}

	return nullptr;
}

bool GenericTree::add(string son, int lands, string father) {
	if (nElements == 0) {
		this->root = new GenericTree::TreeNode(son, lands);
		cout << "Incluiu o root: " << this->root->son << endl;
	}
	else {
		GenericTree::TreeNode* aux = searchNode(father, root);
		if (aux == nullptr)
			return false;
		else
			aux->addSubtree(new GenericTree::TreeNode(son, lands));
	}
	nElements++;
	return true;
}
string GenericTree::getRoot() {
	if (this->root != nullptr)
		return this->root->son;
	throw exception();
}
void GenericTree::setRoot(string son, int lands) {
	if (this->root != nullptr) {
		this->root->son = son;
		this->root->lands = lands;
	}
		
}
string GenericTree::getParent(string son) {
	GenericTree::TreeNode* aux;
	aux = searchNode(son, this->root);
	if ((aux != nullptr) && (aux->father != nullptr))
		return aux->father->son;
	else {
		cout << "aux é nulo? " << ((aux == nullptr) ? "sim" : "não") << endl;
		cout << "pai é nulo? " << ((aux->father == nullptr) ? "sim" : "não") << endl;
	}
	throw exception();
}
bool GenericTree::removeBranch(string son) {
	GenericTree::TreeNode* aux;
	aux = searchNode(son, this->root);
	if (aux != nullptr) {
		if (aux->father != nullptr)
			aux->father->removeSubtree(aux);
		else
			this->root = nullptr;
		removeBranch(aux);
		return true;
	}
	return false;
}
void GenericTree::removeBranch(GenericTree::TreeNode* ref) {
	if (ref != nullptr) {
		for (int i = 0; i < ref->getSubtreeSize(); i++)
			removeBranch(ref->getSubtree(i));
		delete ref;
		nElements--;
	}
}

bool GenericTree::contains(string son) {
	return (searchNode(son, this->root) != nullptr) ? true : false;
}
bool GenericTree::isInternal(string son) {
	GenericTree::TreeNode* aux = searchNode(son, this->root);
	if (aux == nullptr)
		throw exception();
	return aux->getSubtreeSize() > 0 ? true : false;
}
bool GenericTree::isExternal(string son) {
	return !isInternal(son);
}
bool GenericTree::isRoot(string son) {
	if ((this->root != nullptr) && (this->root->son == son))
		return true;
	return false;
}
bool GenericTree::isEmpty() {
	return this->nElements == 0;
}
int GenericTree::size() {
	return nElements;
}
void GenericTree::clear() {
	removeBranch(this->root);
	this->root = nullptr;
	nElements = 0;
}
int* GenericTree::positionPre() { return nullptr; }
int* GenericTree::positionPos() { return nullptr; }
int* GenericTree::positionWidth() { return nullptr; }
void GenericTree::printTree() {
	printTree(this->root);
}
void GenericTree::printTree(GenericTree::TreeNode* ref) {
	if (ref != nullptr) {
		cout << ref->son << "; ";
		for (int i = 0; i < ref->getSubtreeSize(); i++)
			printTree(ref->getSubtree(i));
	}
}

void GenericTree::distribuirTerras()
{
	distribuirTerras(root, 0);
}


void GenericTree::distribuirTerras(TreeNode* node, int terras)
{
	node->lands += terras;
	if (node->getSubtreeSize() > 0)
	{
		int terrasParaCadaFilho = node->lands / node->getSubtreeSize();
		node->lands = 0;
		for (int i = 0; i < node->getSubtreeSize(); i++)
		{
			distribuirTerras(node->getSubtree(i), terrasParaCadaFilho);
		}
	}
}


void GenericTree::getPontas(TreeNode* node, Pessoa* pessoa)
{
	if (node->getSubtreeSize() > 0)
	{
		for (int i = 0; i < node->getSubtreeSize(); i++)
		{
			getPontas(node->getSubtree(i), pessoa);
		}
	} else
	{
		if (node->lands > pessoa->getTerras())
		{
			pessoa->setPessoa(node->son, node->lands);
		}
	}
}


void GenericTree::printPessoaMaisTerras()
{
	Pessoa* pessoa = new Pessoa();

	getPontas(root, pessoa);

	cout << "O guerreiro com mais terras e " << pessoa->getNome() << endl;
	cout << "Ele possui " << pessoa->getTerras() << " terras" << endl;
}
