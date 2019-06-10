#ifndef animatable_hpp
#define animatable_hpp

namespace Game {
    
    template <class T>
    class Animatable {
        
        T value;
        T target;
        double time;
        
    public:
        
        void set(T);
        void to(T, double);
        void update(double);

    };

}

#endif
