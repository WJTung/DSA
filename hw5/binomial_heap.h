#include <utility>
#include <list>

struct EmptyHeap: public std::exception {};

template<class T>
class BinomialHeap {
    private:
        /* inner class: binomial tree */
        struct BinomialTree {
            int _size;
            T element;
            std::list<BinomialTree*> children;

            BinomialTree(T _ele): _size(1), element(_ele) {
                children.clear();
            }

            /* return the size of BinomialTree
             * #note that nullptr->size() == 0
             * (nullptr is a null pointer (like NULL in C))
             */
            int size() {
                return (this!=nullptr)?this->_size:0;
            }
        };
        /* some definition for convinience
         */
        typedef BinomialTree BT;
        typedef BinomialHeap<T> BH;
        typedef std::pair<BT*, BT*> CarrySum;
        typedef std::pair<T, BH> MaxRemainder;

        /* Merge three binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b, c: carry in
         *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
         *          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
         *
         * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
         */
		CarrySum merge_tree(BT *a, BT *b, BT *c) {
			if(a != nullptr) 
			{
				if(b != nullptr) // 1 1 0 or 1 1 1
				{
					if(b->element > a->element)
					{
						b->children.push_back(a);
						b->_size += a->size();
						CarrySum ans;
						ans = std::make_pair(b, c);
						return ans;
					}
					else
					{
						a->children.push_back(b);
						a->_size += b->size();
						CarrySum ans;
						ans = std::make_pair(a, c);
						return ans;
					}
				}
				else
				{
					if(c != nullptr) // 1 0 1
					{
						if(c->element > a->element)
						{
							c->children.push_back(a);
							c->_size += a->size();
							CarrySum ans;
							ans = std::make_pair(c, b);
							return ans;
						}
						else
						{
							a->children.push_back(c);
							a->_size += c->size();
							CarrySum ans;
							ans = std::make_pair(a, b);
							return ans;
						}
					}
					else // 1 0 0
					{
						CarrySum ans;
						ans = std::make_pair(nullptr, a);
						return ans;
					}
				}
			}
			else
			{
				if(b != nullptr)
				{
					if(c != nullptr) // 0 1 1
					{
						if(c->element > b->element)
						{
							c->children.push_back(b);
							c->_size += b->size();
							CarrySum ans;
							ans = std::make_pair(c, a);
							return ans;
						}
						else
						{
							b->children.push_back(c);
							b->_size += c->size();
							CarrySum ans;
							ans = std::make_pair(b, a);
							return ans;
						}
					}
					else // 0 1 0
					{
						CarrySum ans;
						ans = std::make_pair(nullptr, b);
						return ans;
					}
				}
				else // 0 0 0 or 0 0 1
				{
					CarrySum ans;
					ans = std::make_pair(nullptr, c);
					return ans;
				}
			}
        }

        /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
         *
         * INPUT:   a: a pointer of BinomialTree
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: the maximum element
         *          second: a binomial heap consists of other elements
         */
        MaxRemainder pop_max(BT *a) {
			T max = a->element;
			typename std::list<BT *>::iterator i;
			int k;
			BH H;
			for(i = (a->children).begin(); i != (a->children).end(); ++i)
			{
				k = ((*i)->children).size();
				H.trees[k] = (*i);
			}
			H.size = a->_size - 1;
			MaxRemainder ans;
			ans = std::make_pair(max, H);
			return ans;
        }

        BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

    public:
		int size;
        BinomialHeap(): size(0) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): size(1) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
            trees[0] = new BT(element);
        }

        /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
         *
         * INPUT:   b: a reference of BinomialHeap
         */
        void merge(BH &b) {
			BT *carry = nullptr;
			int i;
            for(i = 0; i < 32; i++)
			{
				CarrySum result = merge_tree(this->trees[i], b.trees[i], carry);
				carry = result.first;
				this->trees[i] = result.second;
				b.trees[i] = nullptr;
			}
			this->size += b.size;
			b.size = 0;
        }

        void insert(const T &element) {
            BH tmp = BH(element);
            merge(tmp);
        }
		
		T& find_max() //For a BinomialHeap with size > 0, return the reference of its max element
		{
			int max_tree = -1;
			for(int i=0; i<32; ++i)
				if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
					max_tree = i;
			return trees[max_tree]->element;
		}
		
        T pop() {
            if(size==0) throw EmptyHeap();
            else {
                //find the tree contains maximum element
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;

                MaxRemainder m_r = pop_max(trees[max_tree]);
                T &max_element = m_r.first;
                BH &remainder = m_r.second;

                size -= trees[max_tree]->size();
				delete trees[max_tree];
                trees[max_tree] = nullptr;
                merge(remainder);
                return max_element;
            }
        }
};
