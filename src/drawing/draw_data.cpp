#include "draw_data.h"

void DrawData::Bind()
{
    glBindVertexArray(vao);
}
void DrawData::Unbind()
{
    glBindVertexArray(0);
}
void DrawData::Draw()
{
    Bind();
    glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
}