#include <iostream>
#include <vector>

template <typename T> void permutation(T begin, T end)
{
  typename std::iterator_traits<T>::value_type last_value = *(end-1);

  T it;

  for(it=end-1; it!=begin; it--)
    *it = *(it-1);

  *begin = last_value;
}


int main()
{
  std::vector<char> v;

  v.push_back('a');
  v.push_back('b');
  v.push_back('c');
  v.push_back('d');
  v.push_back('e');


  permutation<std::vector<char>::iterator>(v.begin(), v.end());

  std::vector<char>::iterator it;

  for(it=v.begin(); it!=v.end(); it++)
    std::cout << *it << " ";

  std::cout << std::endl;

  return 0;
}
