#version 130
uniform vec2 bottomLeft;
uniform float scale;
uniform int iter;

out vec4 fragColor;

void main(void)
{
    vec2 z, c, tmp;
    int i;

    c = scale * gl_FragCoord.xy + bottomLeft;
    z = c;

    for (i = 0; i < iter; i++)
    {
        float u = z.x;
        float v = z.y;
        mat2 A = mat2(u, v,
                     -v, u);
        float detA = u*u + v*v;
        z = A*z + c;
        if (detA > 4.0)
            break;
    }

    float col = (i == iter ? 0.0 : 1.0-float(i)/float(iter));
    fragColor = vec4(col, col, col, 1.0f);
}
