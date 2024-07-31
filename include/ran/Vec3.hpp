#ifndef RAN_VEC3_HPP
#define RAN_VEC3_HPP

namespace ran {

union __attribute__((packed, aligned(16)))  Vec3 {
private:
    float dim[4];
public:
    struct {
        float x;
        float y;
        float z;
    };
    Vec3 (float f);
    Vec3 (const Vec3 &vec);
    Vec3 (float x, float y, float z);
    
    inline void add (const Vec3 &vec) __restrict;
    inline void sub (const Vec3 &vec) __restrict;
    
    void cross (const Vec3 &vec);
    
    inline void multiply (float f);

    inline void invert ();
    inline void normalize ();

    inline float dot (const Vec3 &vec) const;

    inline float magnitude () const;
    inline bool zero () const;
};

}

#endif
