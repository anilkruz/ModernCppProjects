#include<iostream>
#include<vector>

using namespace std;
class cus_allocate{
	private:
		char* memory; // pre allocated memory
		size_t block_size;
		size_t total_block;
		vector<void*>freelist; //  store memor
		public:
			cus_allocate(size_t block_size,size_t total_block):block_size(block_size),total_block(total_block){
					memory = new char[block_size*total_block];
					for(size_t i=0;i<total_block;++i){
						freelist.push_back(memory+i*block_size);
					}
				}
			void* allocated(){
				if(freelist.empty()){
					cerr<<"can't allocated"<<endl;
					return nullptr;
				}
				void* t = freelist.back();
				freelist.pop_back();
				return t;
			}
			// deallocation
			void deallocation(void *p){
				freelist.push_back(p);
			}
			~cus_allocate(){
				if(memory)
				{
			//	freelist.clear();
			//	delete[] memory;
			//	memory =nullptr;
			}
		
			}
};
int main(){
	cus_allocate a(1024*1024,1024);
		void* p1 = a.allocated();
		void* p2 = a.allocated();

		a.deallocation(p1);
		a.deallocation(p2);

	return 0;
}
