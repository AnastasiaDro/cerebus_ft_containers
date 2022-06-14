#ifndef NODE_TREE_HPP
#define NODE_TREE_HPP

namespace ft
{
	template <bool B, class T, class U>
	struct enable_because
	{
		typedef T type;
	};

	template <class T, class U>
	struct enable_because<false, T, U>
	{
		typedef U type;
	};

	template<class Data>
	struct Node
	{
		private:
			Node();

		public:
			Node	*node_parent;
			Node	*node_left;
			Node	*node_right;
			bool	red;
			Data	value;

		~Node() {}

		Node(const Node &n) : node_parent(n.node_parent),
								node_left(n.node_left),
								node_right(n.node_right),
								red(n.red),
								value(n.value){}

		Node(const Node *n, const Data &rvalue) : node_parent(n),
												node_left(NULL),
												node_right(NULL),
												red(0),
												value(rvalue) {}


		Node(const Data &v) : node_parent(NULL),
								node_left(NULL),
								node_right(NULL),
								red(0),
								value(v) {}

		Node &operator=(const Node &other)
		{
			if (this != other)
			{
				this->red = other.red;
				this->node_left = other.node_left;
				this->node_parent = other.node_parent;
				this->node_right = other.node_right;
				this->value = other.value;
			}
			return (*this);
		}
	};
}


#endif