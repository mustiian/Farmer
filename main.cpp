#include <iostream>
#include <map>
#include <set>

using namespace std;


class CFarmFair{
public:
    CFarmFair() = default;
    ~CFarmFair() = default;

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
    CFairs( const int& cities, const int& connections,
            const int& meals,  const int& minMeals) :
            m_SumCities(cities), m_SumConnetions(connections),
            m_SumMeals(meals),   m_MinimumMeals(minMeals) {}

    ~CFairs() = default;

    void AddFair( const int& number, const int& meal){
        m_Fairs[ number ].setMeal(meal);
    }

    set<int> getNeighborsOfFair ( const int& number ){
        return m_Fairs[ number ].getNeighborsOfFair();
    }

    void AddConnetion( const int& left, const int& right ){
        m_Fairs[ left ]. AddNeighbor( right );
        m_Fairs[ right ].AddNeighbor( left  );
    }

private:
    int m_SumCities;
    int m_SumConnetions;
    int m_SumMeals;
    int m_MinimumMeals;

    map< int, CFarmFair > m_Fairs;
};



int main(){
    int sumCities, sumConnections,
        sumMeals,  minMeals;
    cin >> sumCities >> sumConnections;
    cin >> sumMeals >> minMeals;

    CFairs fairs(sumCities, sumConnections, sumMeals, minMeals);

    for (int i = 0; i < sumCities; ++i) {
        int meal;
        cin >> meal;
        fairs.AddFair(i, meal);
    }
}