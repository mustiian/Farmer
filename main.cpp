#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>

using namespace std;


class CFarmFair{
public:
    CFarmFair() = default;
    ~CFarmFair() = default;

    int getMeal() const { return m_Meal; }
    void setMeal ( const int& meal ) { m_Meal = meal; }

    void AddNeighbor ( const int& neighbor ){
        m_Neighbors.insert( m_Neighbors.end(), neighbor );
    }

    set<int> getNeighbors () const {
        return m_Neighbors;
    }

private:
    int m_Meal;
    set<int> m_Neighbors;
};

struct TResult{
    TResult () : m_Price(0) {}
    int m_Price;
    set<int> m_allMeals;

    friend ostream& operator <<( ostream &os, const TResult &rhs){
        os << rhs.m_Price;
        for ( auto& meals: rhs.m_allMeals)
            os << " " << meals;
        return os;
    }
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

    void AddConnetion( const int& left, const int& right ){
        m_Fairs[ left ]. AddNeighbor( right );
        m_Fairs[ right ].AddNeighbor( left  );
    }

    vector<TResult> countPrice();
    void    getMealsFromNeighbors( TResult& result, int& connectionCounter,
                                    set<int>& closed, list<int>& queue,
                                    int& distance  ) const;
    TResult BFSFair( const int& number, const CFarmFair& fair ) const;

    void printResult( const vector<TResult>& results ){
        cout << m_MaxPrice << endl;
        for( auto& fair: results)
            cout << fair << endl;
    }

private:
    int m_SumCities;
    int m_SumConnetions;
    int m_SumMeals;
    int m_MinimumMeals;
    int m_MaxPrice = 0;

    map< int, CFarmFair > m_Fairs;
};

vector<TResult> CFairs::countPrice() {
    vector<TResult> results;

    for (auto& fair : m_Fairs){
        if ( m_MinimumMeals == 1 ){
            TResult result = TResult();
            result.m_allMeals.insert(result.m_allMeals.end(), fair.second.getMeal() );
            results.emplace_back( result );
        }
        else{
            results.push_back( BFSFair(fair.first, fair.second) );
            m_MaxPrice += results.back().m_Price;
        }
    }

    return results;
}

TResult CFairs::BFSFair( const int& number, const CFarmFair& fair ) const{
    int distance = 0, connectionCounter = 0;
    set<int> closed;
    list<int> queue;
    TResult result = TResult();

    queue.push_back( number );
    connectionCounter++;
    distance++;

    result.m_allMeals.insert( result.m_allMeals.begin(), fair.getMeal() );

    while ( !queue.empty() ){
        int tmpConnectionCounter = connectionCounter;

        for (int i = tmpConnectionCounter; i > 0; --i) {
            getMealsFromNeighbors( result, connectionCounter, closed, queue, distance );
            if (result.m_allMeals.size() == (size_t)m_MinimumMeals){
                return result;
            }
        }

        distance++;
    }

    return result;
}

void CFairs::getMealsFromNeighbors( TResult& result, int& connectionCounter,
                                    set<int>& closed, list<int>& queue,
                                    int& distance ) const{
    for (auto &neighbor : m_Fairs.at( queue.front() ).getNeighbors() ) {
        if (closed.find(neighbor) == closed.end()) {
            int neighborMeal = m_Fairs.at(neighbor).getMeal();
            queue.push_back(neighbor);
            connectionCounter++;
            if (result.m_allMeals.find(neighborMeal) == result.m_allMeals.end()) {
                result.m_Price += distance;
                result.m_allMeals.insert(result.m_allMeals.begin(), neighborMeal);
            }

            if (result.m_allMeals.size() == (size_t)m_MinimumMeals)
                return;
        }
    }
    closed.insert(closed.end(), queue.front());
    queue.pop_front();
    connectionCounter --;
}

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

    for (int j = 0; j < sumConnections; ++j) {
        int left, right;
        cin >> left >> right;
        fairs.AddConnetion(left, right);
    }

    fairs.printResult( fairs.countPrice() );

    return 1;
}