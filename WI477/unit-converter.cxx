#include<iostream>
#include<type_traits>
enum class Unit{ km, m, cm };//1____________________
template<int v, Unit u> struct Measure{//2_________________
public:
static const int valor=v;
static const Unit unit=u;
};

template<Unit from, Unit to> struct Measure_convert{

static const int factor = 1;

};

template<>
struct Measure_convert<Unit::km, Unit::m>{

static const int factor = 1000;

};

template<>
struct Measure_convert<Unit::m, Unit::cm>{

static const int factor = 100;

};

template<>
struct Measure_convert<Unit::km, Unit::cm>{

static const int factor = Measure_convert<Unit::km,Unit::m>::factor
                        * Measure_convert<Unit::m,Unit::cm>::factor;

};

template<typename A, typename B> struct Measure_add{//3_________________________



static const int valor = A::valor * Measure_convert<A::unit,B::unit>::factor
                       + B::valor * Measure_convert<B::unit,A::unit>::factor;

static const Unit unit = std::conditional< A::unit < B::unit,
                                            typename B::unit,
                                            typename A::unit>::type;

};




int main()//4______________________________
        {
           std::cout << Measure_add< Measure<10,Unit::km>, Measure<20,Unit::m> >::valor  << std::endl;
           std::cout << Measure_add< Measure<10,Unit::cm>, Measure<20,Unit::km> >::valor << std::endl;

            return 0;
        }
