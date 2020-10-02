#version 130
uniform vec3 bottomLeft;
uniform vec3 modulus;
uniform float scale;
uniform int iter;

out vec4 fragColor;

void main(void)
{
    float a = modulus.x, b = modulus.y; // Coefficients of t^2 + at + b = 0, from the modulus polynomial
    vec2 X, B;
    int i;

    mat2 T = mat2(0, 1, -b, -a);
    mat2 I = mat2(1, 0, 0, 1);
    B = scale * gl_FragCoord.xy + bottomLeft.xy;
    X = B;
    for (i = 0; i < iter; i++)
    {
        mat2 A = X.y*T + X.x*I;
        X = A*X + B;
        if (X.x*X.x + X.y*X.y > 4.0f)
            break;
    }

    float col = (i == iter ? 0.0 : 1.0-float(i)/float(iter));
    fragColor = vec4(col, col, col, 1.0f);
}
