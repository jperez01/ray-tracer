#pragma once

#include "shapes/group.h"
#include "shapes/triangle.h"

#include <sstream>
#include <string>
#include <vector>

class ObjGroup {
    public:
        ObjGroup(std::string name) { m_name = name; }
        ~ObjGroup() = default;

        Group *toGroup(Material &material);

        void addFace(Shape* shape);
        inline std::string name() { return m_name; }

    private:
        std::string m_name;
        std::vector<Shape *> m_faces;
};

struct FaceVertex {
    int vertex;
    int texture_vertex;
    int vertex_normal;
};

class ObjParser {
    public:
        ObjParser(std::stringstream &ss);
        ~ObjParser() = default;

        Tuple vertexAt(int v);
        Tuple normalAt(int n);

        Group* defaultGroup();
        Group* groupNamed(std::string name);
        Group* superGroup();

        void setMaterial(Material &material);

    private:
        void parseLine(std::string &line);
        std::vector<FaceVertex> parseFaceVertices(std::string &vertices);
        std::vector<float> parseFloats(std::string &numbers);

        void addVertex(std::string coords);
        void addNormal(std::string vector);
        void addFace(std::string vertices);
        void addGroup(std::string name);

        Material m_material;
        std::vector<Tuple> m_vertices;
        std::vector<Tuple> m_normals;

        std::vector<ObjGroup *> m_groups;
};