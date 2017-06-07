#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// 使用するデータ数
#define DATA_SIZE 1000000

// 2次元座標を扱うためのクラス
class Point {
public:
	int x;
	int y;

	Point() {
		this->x = 0;
		this->y = 0;
	}

	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	void showPoint() {
		printf("(x, y) = (%3d, %3d)\n", this->x, this->y);
	}
};

// ツリーの各ノードを扱うクラス
class Node {
private:
	Point point;
	Node *left;
	Node *right;
public:
	Node() {
		this->left = nullptr;
		this->right = nullptr;
	}

	Node(Point p) {
		this->point = p;
		this->left = nullptr;
		this->right = nullptr;
	}

	void setPoint(Point p) {
		this->point = p;
	}

	Point getPoint() {
		return this->point;
	}

	void setLeft(Node *n) {
		this->left = n;
	}

	Node *getLeft() {
		return this->left;
	}

	void setRight(Node *n) {
		this->right = n;
	}

	Node *getRight() {
		return this->right;
	}
};

// ベクターをfromからtoまで取り出する関数
template<typename T>
vector<T> divisionVector(std::vector<T> v, int from, int to) {

	//　分離する場所がベクターのサイズ外の場合もとのゔvectorを返す
	if (v.size() < from || v.size() < to ||
		0 > from || 0 > to || (to < from)) {
		vector<T> zero(0);
		return zero;
	}

	std::vector<T> result;
	for (int i = from; i < to; i++) {
		result.push_back(v[i]);
	}
	return result;
}

// ２次元木
class KDTree {
private:
	Node *root;

public:
	KDTree() {
		this->root = nullptr;
	}


	void setData(std::vector<Point> v) {
		cout << "data_size = " << v.size() << "\n\n";
		this->root = this->setChildren(v, 0);

		// デバッグ用
		// for (auto i = v.begin(); i != v.end(); i++) {
		// 	cout << "(x, y) = " 
		// 	<< "(" << i->x << ", " << i->y << ")" << endl;
		// }
	}

	void showTree(int n) {
		if (n == 0) {
			this->preOrder(this->root);
		}
		if (n == 1)
			this->inOrder(this->root);
	}

private:

	void preOrder(Node *root) {
		if (root != nullptr) {
			root->getPoint().showPoint();
			preOrder(root->getLeft());
			preOrder(root->getRight());
		}
	}

	void inOrder(Node *root) {
		if (root != nullptr) {
			inOrder(root->getLeft());
			root->getPoint().showPoint();
			inOrder(root->getRight());
		}
	}

	Node *setChildren(std::vector<Point> v, int depth) {
		cout << "depth = " << depth << endl;
		cout << "v.size() = " << v.size() << endl;

		if (v.size() == 1) {
			Node *n = new Node();
			n->setPoint(v[0]);
			cout << "leaf" << endl;
			n->getPoint().showPoint();
			return n;
		}
		else if (v.size() == 0) {
			return nullptr;
		}

		Node *newNode = new Node();
		if (depth % 2 == 0) {
			sort(v.begin(), v.end(),
				[](auto a, auto b) {
				return a.y < b.y;
			});
		}
		else {
			sort(v.begin(), v.end(),
				[](auto a, auto b) {
				return a.x < b.x;
			});
		}

		printf("0 ~ %d, %d, %d ~ %d\n", v.size() / 2 - 1, v.size() / 2, v.size() / 2 + 1, v.size());
		newNode->setPoint(v[v.size() / 2]);
		newNode->getPoint().showPoint();

		if (v.size() / 2 - 1 >= 0) {
			auto leftvector = divisionVector<Point>(v, 0, v.size() / 2);
			if (leftvector.size() != 0) {
				cout << "\nleft" << endl;
				newNode->setLeft(this->setChildren(leftvector, depth + 1));
			}
			else {
				newNode->setLeft(nullptr);
			}
		}
		else {
			newNode->setLeft(nullptr);
		}

		if (v.size() / 2 + 1 < DATA_SIZE && v.size() / 2 + 1 < v.size()) {
			auto rightvector = divisionVector<Point>(v, v.size() / 2 + 1, v.size());
			if (rightvector.size() != 0) {
				cout << "\nright" << endl;
				newNode->setRight(this->setChildren(rightvector, depth + 1));
			}
			else {
				newNode->setRight(nullptr);
			}
		}
		else {
			newNode->setRight(nullptr);
		}

		return newNode;
	}
};

int main(void) {
	srand((unsigned int)time(NULL));

	// 座標を保存変数
	std::vector<Point> Points;

	// kd木
	KDTree kd;

	//　重複のないランダムな座標を生成する
	for (int i = 0; i < DATA_SIZE; i++) {
		Point p = Point(i, rand() % DATA_SIZE);
		Points.push_back(p);
	}
	shuffle(Points.begin(), Points.end(), mt19937());
	for (int i = 0; i < DATA_SIZE; i++) {
		Points[i].y = i;
	}


	// kd木にデータをセットする
	printf("start\n");
	//for (auto i = Points.begin(); i != Points.end(); i++) {
	//	i->showPoint();
	//}

	kd.setData(Points);

	printf("\nshow result\n");
	kd.showTree(0);
	printf("\n");
	//kd.showTree(1);
	return 0;
}