#version 130
uniform vec3 bottomLeft;
uniform vec3 modulus;
uniform float scale;
uniform int iter;

out vec4 fragColor;

vec4 getColor(int i)
{
    int wraps = 2;

    if (i == iter)
        return vec4(0.0f, 0.0f, 0.0f, 1.0f);

    vec4 colors[4];
    colors[0] = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    colors[1] = vec4(1.0f, 0.0f, 0.0f, 0.25f);
    colors[2] = vec4(1.0f, 1.0f, 0.0f, 0.50f);
    colors[3] = vec4(1.0f, 0.0f, 0.0f, 0.75f);

    float a = float(wraps)*float(i)/float(iter);
    a -= float(int(a));

    int j = 0, k = 1;
    // Increment j and k until colors[j].a <= a < colors[k].a
    while ( (k < colors.length()) && (colors[k].a <= a) )
    {
        j++;
        k++;
    }
    if (k == colors.length())
        k = 0;

    float s = (a - colors[j].a)/(colors[k].a - colors[j].a);
    //float t = s*s*(3.0f - 2.0f*s);
    float t = s;

    vec3 col = (1.0f - t)*colors[j].rgb + t*colors[k].rgb;
    return vec4(col, 1.0f);
}

void main(void)
{
    // Coefficients of t^3 + at^2 + bt + c = 0, from the modulus polynomial
    float a = modulus.x;
    float b = modulus.y;
    float c = modulus.z;
    vec3 X, B;
    int i;

    mat3 T = mat3(0, 1, 0, 0, 0, 1, -c, -b, -a);
    mat3 I = mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    vec3 tmp = vec3(gl_FragCoord.x, gl_FragCoord.y, 0);
    B = scale*tmp + bottomLeft;
    X = B;
    for (i = 0; i < iter; i++)
    {
        mat3 A = (X.z*T + X.y*I)*T + X.x*I;
        X = A*X + B;
        if (X.x*X.x + X.y*X.y + X.z*X.z > 4.0f)
            break;
    }

    fragColor = getColor(i);
}
