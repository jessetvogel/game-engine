uniform vec3 uPosition;
varying vec2 vUV;

#define MIN_DIST (0.001)
#define MAX_DIST (1000.0)
#define MAX_STEPS (50)

#define BLACK vec4(0.0, 0.0, 0.0, 1.0)
#define WHITE vec4(1.0, 1.0, 1.0, 1.0)
#define SKY vec4(0.5, 1.0, 1.0, 1.0)


vec4 GetLight(vec3);

float GetDist(vec3 p) {
    vec3 sphere = vec3(4.0, 1.0, 0.5);
    float radius = 0.5;
    
    float distSphere = length(sphere - p) - radius;
    float distPlane = p.z;
    
    return min(distPlane, distSphere);
}

vec4 RayMarch(vec3 p, vec3 dir) {
    float d = 0.0;
    for(int i = 0;i < MAX_STEPS; ++i) {
        float dist = GetDist(p + dir * d);
        d += dist;
        
        if(dist < MIN_DIST)
            return GetLight(p + dir * d);
        
        if(d > MAX_DIST)
            return SKY;
        
        d += dist;
    }
    
    return SKY;
}


vec3 GetNormal(vec3 p) {
    float d = GetDist(p);
    vec2 e = vec2(0.01, 0.0);
    
    vec3 n = vec3(d - GetDist(p - e.xyy),
                  d - GetDist(p - e.yxy),
                  d - GetDist(p - e.yyx));
    
    return normalize(n);
}


vec4 GetLight(vec3 p) {
    vec3 lightPosition = vec3(0.0, 50.0, 100.0);
    vec3 l = normalize(lightPosition - p);
    vec3 n = GetNormal(p);
    
    
    float shadow = dot(n, l);
    if(shadow < 0.0)
        shadow = 0.0;
    
    
    float d = RayMarch(p + 2.0 * MIN_DIST * l, l);
    if(d < length(l))
        shadow *= 0.5;

    
    return vec4(vec3(1.0, 1.0, 1.0) * shadow, 1.0);
}





void main() {
    vec3 rayOrigin = uPosition;
    vec3 rayDirection = normalize(vec3(1.0, vUV));
    
    gl_FragColor = RayMarch(rayOrigin, rayDirection);
}
