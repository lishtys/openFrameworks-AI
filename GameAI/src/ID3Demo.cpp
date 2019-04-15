/*************************************************
Copyright:1.0
Author:90Zeng
Date:2014-11-25
Description:ID3/C4.5 algorithm
**************************************************/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>
#include "ID3Demo.h"
using namespace std;


const unsigned att_num = 3;
const unsigned rule_num = 14;
string decision_tree_name("Chase Node ?");
string attribute_names[] = { "Status", "Distance", "In Respawn" };
string attribute_values[] = { "Visable", "invisible", "Respawn",
"<=20", ">20", "True", "False", "Yes", "No" };
unsigned train_data[rule_num][att_num + 1] = {
					{0, 3, 6, 8},{0, 3, 5, 8},{1, 3, 6, 7},
					{2, 3, 6, 7},{2, 3, 6, 7},{2, 4, 5, 8},
					{1, 4, 5, 7},{0, 3, 6, 8},{0, 4, 6, 7},
					{2, 3, 6, 7},{0, 4, 5, 7},{1, 3, 5, 7},
					{1, 4, 6, 7},{2, 3, 5, 8}
};





template <typename T>
vector<T> unique(vector<T> vals)
{
	vector<T> unique_vals;
	vector<T>::iterator itr;
	vector<T>::iterator subitr;

	int flag = 0;
	while (!vals.empty())
	{
		unique_vals.push_back(vals[0]);
		itr = vals.begin();
		subitr = unique_vals.begin() + flag;
		while (itr != vals.end())
		{
			if (*subitr == *itr)
				itr = vals.erase(itr);
			else
				itr++;
		}
		flag++;
	}
	return unique_vals;
}


double log2(double n)
{
	return log10(n) / log10(2.0);
}


double compute_entropy(vector<unsigned> v)
{
	vector<unsigned> unique_v;
	unique_v = unique(v);

	vector<unsigned>::iterator itr;
	itr = unique_v.begin();

	double entropy = 0.0;
	auto total = v.size();
	while (itr != unique_v.end())
	{
		double cnt = count(v.begin(), v.end(), *itr);
		entropy -= cnt / total * log2(cnt / total);
		itr++;
	}
	return entropy;
}

vector<double> compute_gain(vector<vector<unsigned> > truths)
{
	vector<double> gain(truths[0].size() - 1, 0);
	vector<unsigned> attribute_vals;
	vector<unsigned> labels;
	for (unsigned j = 0; j < truths.size(); j++)
	{
		labels.push_back(truths[j].back());
	}

	for (unsigned i = 0; i < truths[0].size() - 1; i++)
	{
		for (unsigned j = 0; j < truths.size(); j++)
			attribute_vals.push_back(truths[j][i]);

		vector<unsigned> unique_vals = unique(attribute_vals);
		vector<unsigned>::iterator itr = unique_vals.begin();
		vector<unsigned> subset;
		while (itr != unique_vals.end())
		{
			for (unsigned k = 0; k < truths.size(); k++)
			{
				if (*itr == attribute_vals[k])
				{
					subset.push_back(truths[k].back());
				}
			}
			double A = (double)subset.size();
			gain[i] += A / truths.size() * compute_entropy(subset);
			itr++;
			subset.clear();
		}
		gain[i] = compute_entropy(labels) - gain[i];
		attribute_vals.clear();
	}
	return gain;
}



vector<double> compute_gain_ratio(vector<vector<unsigned> > truths)
{
	vector<double> gain = compute_gain(truths);
	vector<double> entropies;
	vector<double> gain_ratio;

	for (unsigned i = 0; i < truths[0].size() - 1; i++)
	{
		vector<unsigned> attribute_vals(truths.size(), 0);
		for (unsigned j = 0; j < truths.size(); j++)
		{
			attribute_vals[j] = truths[j][i];
		}
		double current_entropy = compute_entropy(attribute_vals);
		if (current_entropy)
		{
			gain_ratio.push_back(gain[i] / current_entropy);
		}
		else
			gain_ratio.push_back(0.0);

	}
	return gain_ratio;
}


template <typename T>
T find_most_common_label(vector<vector<T> > data)
{
	vector<T> labels;
	for (unsigned i = 0; i < data.size(); i++)
	{
		labels.push_back(data[i].back());
	}
	vector<T>::iterator itr = labels.begin();
	T most_common_label;
	unsigned most_counter = 0;
	while (itr != labels.end())
	{
		unsigned current_counter = count(labels.begin(), labels.end(), *itr);
		if (current_counter > most_counter)
		{
			most_common_label = *itr;
			most_counter = current_counter;
		}
		itr++;
	}
	return most_common_label;
}


template <typename T>
vector<T> find_attribute_values(T attribute, vector<vector<T> > data)
{
	vector<T> values;
	for (unsigned i = 0; i < data.size(); i++)
	{
		values.push_back(data[i][attribute]);
	}
	return unique(values);
}


template <typename T>
vector<vector<T> > drop_one_attribute(T attribute, vector<vector<T> > data)
{
	vector<vector<T> > new_data(data.size(), vector<T>(data[0].size() - 1, 0));
	for (unsigned i = 0; i < data.size(); i++)
	{
		data[i][attribute] = 110;
	}
	return data;
}


struct Tree {
	unsigned root;
	vector<unsigned> branches;
	vector<Tree> children; 
};


void build_decision_tree(vector<vector<unsigned> > examples, Tree &tree)
{
	vector<unsigned> labels(examples.size(), 0);
	for (unsigned i = 0; i < examples.size(); i++)
	{
		labels[i] = examples[i].back();
	}
	if (unique(labels).size() == 1)
	{
		tree.root = labels[0];
		return;
	}


	if (count(examples[0].begin(), examples[0].end(), 110) == examples[0].size() - 1)
	{
		tree.root = find_most_common_label(examples);
		return;
	}


	vector<double> standard = compute_gain(examples);

	
	tree.root = 0;
	for (unsigned i = 0; i < standard.size(); i++)
	{
		if (standard[i] >= standard[tree.root] && examples[0][i] != 110)
			tree.root = i;
	}


	tree.branches = find_attribute_values(tree.root, examples);
	vector<vector<unsigned> > new_examples = drop_one_attribute(tree.root, examples);
	vector<vector<unsigned> > subset;
	for (unsigned i = 0; i < tree.branches.size(); i++)
	{
		for (unsigned j = 0; j < examples.size(); j++)
		{
			for (unsigned k = 0; k < examples[0].size(); k++)
			{
				if (tree.branches[i] == examples[j][k])
					subset.push_back(new_examples[j]);
			}
		}
		Tree new_tree;
		build_decision_tree(subset, new_tree);
		tree.children.push_back(new_tree);
		subset.clear();
	}
}

void print_tree(Tree tree, unsigned depth)
{
	for (unsigned d = 0; d < depth; d++) cout << "\t";
	if (!tree.branches.empty()) // Not Leaf Node
	{
		cout << attribute_names[tree.root] << endl;

		for (unsigned i = 0; i < tree.branches.size(); i++)
		{
			for (unsigned d = 0; d < depth + 1; d++) cout << "\t";
			cout << attribute_values[tree.branches[i]] << endl;
			print_tree(tree.children[i], depth + 2);
		}
	}
	else // leaf Node
	{
		cout << attribute_values[tree.root] << endl;
	}

}






ID3Demo::ID3Demo()
{
}


ID3Demo::~ID3Demo()
{
}

void ID3Demo::Draw()
{
}

void ID3Demo::Init()
{
	vector<vector<unsigned> > rules(rule_num, vector<unsigned>(att_num + 1, 0));
	for (unsigned i = 0; i < rule_num; i++)
	{
		for (unsigned j = 0; j <= att_num; j++)
			rules[i][j] = train_data[i][j];
	}
	Tree tree;
	build_decision_tree(rules, tree);
	cout << decision_tree_name << endl;
	print_tree(tree, 0);
}

void ID3Demo::Update()
{
	
}






