#version 130
uniform vec2 bottomLeft;
uniform vec2 modulus;
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
    B = scale * gl_FragCoord.xy + bottomLeft;
    X = B;
    for (i = 0; i < iter; i++)
    {
        float x = X.x, y = X.y; // Coefficients of yt + x, from the given point
        mat2 A = y*T + x*I;

        // Determinant of A
        float detA = A[0][0]*A[1][1] - A[1][0]*A[0][1];
        X = A*X + B;

        // This is just a guess...
        if (detA > 4.0f)
            break;
    }

    float col = (i == iter ? 0.0 : 1.0-float(i)/float(iter));
    fragColor = vec4(col, col, col, 1.0f);
}
