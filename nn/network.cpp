#include <vector>

class CNN 
{
    public:
        CNN(int numberOfLayersC_, int numberOfLayersP_) {
            numberOfLayersC = numberOfLayersC_;
            numberOfLayersP = numberOfLayersP_;
        }
        ~CNN() {
            a.~vector();
        }

    private:
        int numberOfLayersC, numberOfLayersP;
        std::vector<int> a;
};Ваня Грибанов лох