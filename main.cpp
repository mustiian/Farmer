#include <iostream>
#include <map>
#include <set>

using namespace std;


class CFarmFair{
public:
    CFarmFair() {}
    ~CFarmFair() {}

    int getMeal() { return m_Meal; }
    void setMeal ( const int& meal ) { m_Meal = meal; }

    void AddNeighbor ( const int& neighbor ){
        m_Neighbors.insert( m_Neighbors.begin(), neighbor );
    }

    set<int> getNeighborsOfFair ( ) {
        return m_Neighbors;
    }

private:
    int m_Meal;
    set<int> m_Neighbors;
};

class CFairs{
public:
    CFairs() {}
    ~CFairs() {}

    set<int> getNeighborsOfFair ( const int& number ){
        return m_Fairs[ number ].getNeighborsOfFair();
    }


private:
    int m_SumCities;
    int m_SumConnetions;
    int m_SumMeals;
    int m_MinimumMeals;

    map< int, CFarmFair > m_Fairs;
};



int main(){

}