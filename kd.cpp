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
#define DATA_SIZE 100

// 2次元座標を扱うためのクラス
class Point {
public :
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

};

// ツリーの各ノードを扱うクラス
class Node {
private :
	Point p;
	Node *left;
	Node *right;
public :
	Node() {
		this->left = nullptr;
		this->right = nullptr;
	}

	Node(Point p) {
		this->p = p;
		this->left = nullptr;
		this->right = nullptr;
	}

	void setLeft(Node *n) {
		this->left = n;
	}

	void setRight(Node *n) {
		this->right = n;
	}

};

// ベクターをfromからtoまで取り出する関数
template<typename T>
vector<T> divisionVector(std::vector<T> v, int from, int to) {

	//　分離する場所がベクターのサイズ外の場合nullを返す
	if (v.size() <= from || v.size() <= to ||
			0 > from || 0 > to || (to < from)) {
		return NULL;
	}

	std::vector<T> result;
	for (int i = from; i < to; i++) {
		result.push_back(v[i]);
	}
	return result;
}

// ２次元木
class KDTree {
private :
	Node *root;

public :
	KDTree() {
		this->root = nullptr;
	}


	void setData(std::vector<Point> v) {

		// y軸に沿ってソートする
		sort(v.begin(), v.end(),
				[](auto a, auto b) {
					return a.y < b.y;
				});


		// 中点を取る
		Node n = Node(v[v.size() / 2]);
		this->root = &n;
		auto leftvector = divisionVector(v, 0, v.size() / 2 - 1);
		auto rightvector = divisionVector(v, v.size() / 2 + 1, v.size());
		this->root->setLeft(this->setChildren(leftvector, 1));

		// デバッグ用
		// for (auto i = v.begin(); i != v.end(); i++) {
		// 	cout << "(x, y) = " 
		// 	<< "(" << i->x << ", " << i->y << ")" << endl;
		// }
	}

private :
	Node *setChildren(std::vector<Point> v, int depth) {
		// 深さが偶数のときはy軸でソートし、
		// 基数のときはx軸でソートする。
	}
};

int main(void) {
	srand((unsigned int)time(NULL));

	// 座標を保存変数
	std::vector<Point> Points;

	// kd木
	KDTree kd;

	for (int i = 0; i < DATA_SIZE; i++) {
			Point p = Point(rand() % DATA_SIZE, rand() % DATA_SIZE);
			Points.push_back(p);
	}

	// kd木にデータをセットする
	kd.setData(Points);
	return 0;
}