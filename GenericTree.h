#include <iostream>
#include "Pessoa.h";

using namespace std;

class GenericTree {
private:
	class TreeNode {
	private:
		int nChild;
		TreeNode** children;
		int vetSize;
		void grow();
	public:
		TreeNode* father;
		string son;
		int lands;
		TreeNode(string son, int lands);
		void addSubtree(TreeNode* n);
		bool removeSubtree(TreeNode* ref);
		TreeNode* getSubtree(int i);
		int getSubtreeSize();
	};
	int nElements;
	TreeNode* root;
	TreeNode* searchNode(string son, TreeNode* ref);
	void printTree(GenericTree::TreeNode* ref);
	void removeBranch(GenericTree::TreeNode* ref);
	void getPontas(TreeNode* node, Pessoa* pessoa);
	void distribuirTerras(TreeNode* node, int terras);
public:
	GenericTree();
	bool add(string son, int lands, string father);
	string getRoot();
	void setRoot(string son, int lands);
	string getParent(string son);
	bool removeBranch(string son);
	bool contains(string son);
	bool isInternal(string son);
	bool isExternal(string son);
	bool isRoot(string son);
	bool isEmpty();
	int size();
	void clear();
	int* positionPre();
	int* positionPos();
	int* positionWidth();
	void printTree();
	void printPessoaMaisTerras();
	void distribuirTerras();
};
