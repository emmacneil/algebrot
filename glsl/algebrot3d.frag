#version 130
uniform sampler2D texSampler;
uniform vec3 bottomLeft;
uniform vec3 modulus;
uniform float scale;
uniform int iter;

out vec4 fragColor;

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

    // Sample color from texture
    vec2 P = vec2(i == iter ? 0.0 : 1.0-float(i)/float(iter), 0.0f);
    fragColor = texture2D(texSampler, P);
}
