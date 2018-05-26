#ifndef range_h
#define range_h

#include <stdexcept>

namespace GPS
{
    template<typename T, T min, T max>
    class Range
    {
    private:
        using value_type = T;
        
        value_type value_;
        
    public:
        Range(const value_type value)
        {
            if (min > value || max <= value)
            {
                throw std::out_of_range("Value out of range");
            }
            value_ = value;
        }
        
        value_type getValue() const
        {
            return value_;
        }
    };
}
#endif 
