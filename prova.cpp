#include<random>
#include<iostream>

std::random_device rd;
std::default_random_engine engine(rd());

int random_call(int const max_exit, int current_road) {   //extract a random exit
  std::uniform_int_distribution<int> unif(1,max_exit);
  int assigned_exit = unif(engine);
  while ((assigned_exit > max_exit) || (assigned_exit == 0) || (assigned_exit==current_road)) {
    assigned_exit = unif(engine);
  }
  return assigned_exit;
}

int main(){
    for (int i = 0; i < 100; i++)
    {
        std::cout << random_call(4,1);
    }
    
}