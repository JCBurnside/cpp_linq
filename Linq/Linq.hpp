#pragma once
#include <functional>
#include <algorithm>
#include <vector>
namespace Linq
{

    template<typename TSource,typename TData = std::vector<TSource>>
    class LinqWrapper
    {
        TData data;
    public:
        LinqWrapper(TData& data) : data(data){}
        LinqWrapper(std::initializer_list<TSource> elems) : data(elems){}
        // aggregates the data through func
        TSource Aggregate(std::function<TSource(TSource&,TSource&)> func)
        {
            if(std::begin(data)==std::end(data))
            {
                throw -1; 
            }
            TSource result= *std::begin(data);
            for(decltype(std::begin(data)) t=std::begin(data)+1;t!=std::end(data);++t)
            {
                result=func(result,*t);
            }
            return result;
        }

        template<typename TAccumulate>
        TAccumulate Aggregate(TAccumulate seed,std::function<TAccumulate(TAccumulate,TSource&)> func)
        {
            if(std::begin(data)==std::end(data))
            {
                throw -1;
            }
            TAccumulate result = seed;
            for(TSource& t : data)
            {
                result = func(result,t);
            }
            return result;
        }

        template<typename TAccumulate, typename TResult>
        TResult Aggregate(TAccumulate seed, std::function<TAccumulate(TAccumulate,TSource&)> func, TResult TAccumulate::* selector)
        {
            TAccumulate result=seed;
            for(TSource& t : data)
            {
                result=func(result,t);
            }
            return result.*selector;
        }

        template<typename TAccumulate, typename TResult>
        TResult Aggregate(TAccumulate seed, std::function<TAccumulate(TAccumulate,TSource&)> func, std::function<TResult(TAccumulate)> selector)
        {
            TAccumulate result=seed;
            for(TSource& t : data)
            {
                result=func(result,t);
            }
            return selector(result);
        }
        
        bool Any(std::function<bool(TSource)> pred)
        {
            return std::any_of(std::begin(data),std::end(data),pred);
        }

        bool Any()
        {
            return std::begin(data) != std::end(data);
        }

        bool All(std::function<bool(TSource)> pred)
        {
            return std::all_of(std::begin(data),std::end(data),pred);
        }

        bool None(std::function<bool(TSource)> pred)
        {
            return std::none_of(std::begin(data),std::end(data),pred);
        }

        bool None()
        {
            return std::begin(data) == std::end(data);
        }
    };

}