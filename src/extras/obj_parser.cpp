#include "extras/obj_parser.h"
#include "shapes/triangle.h"
#include "shapes/smooth_triangle.h"

#include <iostream>
#include <cassert>

void ObjGroup::addFace(Shape* face) {
    m_faces.push_back(face);
}

Group* ObjGroup::toGroup(Material &material) {
    Group *group = new Group(material);
    for (auto &face : m_faces) {
        group->addShape(face);
    }

    return group;
}

ObjParser::ObjParser(std::stringstream &ss) {
    m_material = Material{};
    m_groups.push_back(new ObjGroup(""));

    std::string line;
    while (std::getline(ss, line, '\n')) parseLine(line);
}

Tuple ObjParser::vertexAt(int v) {

    if (v > 0) {
        std::vector<Tuple>::size_type index = v - 1;
        assert(index < m_vertices.size());
        return m_vertices[index];
    } else {
        std::vector<Tuple>::size_type index = v + 1;
        assert(abs(v) <= m_vertices.size());
        return m_vertices[m_vertices.size() - 1 + index];
    }
}

Tuple ObjParser::normalAt(int n) {
    assert(n != 0);
    if (n > 0) {
        std::vector<Tuple>::size_type index = n - 1;
        assert(index < m_vertices.size());
        return m_vertices[index];
    } else {
        assert(abs(n) <= m_vertices.size());
        return m_vertices[m_vertices.size() + n];
    }
}

void ObjParser::parseLine(std::string &line) {
    if (line.length() < 3) return;

    if (line.find("v ") == 0) addVertex(line.substr(2));
    else if (line.find("f ") == 0) addFace(line.substr(2));
    else if (line.find("g ") == 0) addGroup(line.substr(2));
    else if (line.find("vn ") == 0) addNormal(line.substr(3));
    else {
        std::cout << "Unparsable: " << line << std::endl;
    }
}

std::vector<float> ObjParser::parseFloats(std::string &numbers) {
    std::vector<float> parsed;
    std::string num;
    std::stringstream ss = std::stringstream(numbers);

    while (std::getline(ss, num, ' ')) {
        if (num.size()) parsed.push_back(stof(num));
    }

    return parsed;
}

void ObjParser::addVertex(std::string coords) {
    std::vector<float> nums = parseFloats(coords);

    assert(nums.size() == 3);
    Tuple v = Point(nums[0], nums[1], nums[2]);
    m_vertices.push_back(v);
}

void ObjParser::addGroup(std::string name) {
    ObjGroup* group = new ObjGroup(name);
    m_groups.push_back(group);
}

void ObjParser::addNormal(std::string vector) {
    std::vector<float> nums = parseFloats(vector);

    assert(nums.size() == 3);
    Tuple n = Vector(nums[0], nums[1], nums[2]);
    m_normals.push_back(n);
}

void ObjParser::addFace(std::string vertices) {
    std::vector<FaceVertex> faces = parseFaceVertices(vertices);
    assert(faces.size() >= 3);

    for (std::vector<FaceVertex>::size_type i = 1; i < faces.size(); ++i) {
        int vn0 = faces[0].vertex_normal;
        int vni = faces[i].vertex_normal;
        int vni1 = faces[i+1].vertex_normal;

        if (vn0 == 0 && vni == 0 && vni1 == 0) {
            Tuple v1 = vertexAt(faces[0].vertex),
                v2 = vertexAt(faces[i].vertex),
                v3 = vertexAt(faces[i+1].vertex);
            Triangle* face = new Triangle(v1, v2, v3);
            m_groups[m_groups.size() - 1]->addFace(face);
        } else {
            Tuple v1 = vertexAt(faces[0].vertex),
                v2 = vertexAt(faces[i].vertex),
                v3 = vertexAt(faces[i+1].vertex);
            Tuple vn1 = normalAt(vn0), vn2 = normalAt(vni), vn3 = normalAt(vni1);
            SmoothTriangle* face = new SmoothTriangle(v1, v2, v3, vn1, vn2, vn3);
            m_groups[m_groups.size() - 1]->addFace(face);
        }
    }
}

std::vector<FaceVertex> ObjParser::parseFaceVertices(std::string &vertices) {
    std::vector<FaceVertex> face_vertices;
    std::string vertex_string;
    std::stringstream ss = std::stringstream(vertices);

    while(std::getline(ss, vertex_string, ' ')) {
        std::string fv;
        std::stringstream fvss = std::stringstream(vertex_string);
        int vertex = 0, texture = 0, normal = 0;

        if (std::getline(fvss, fv, '/')) {
            if (fv.length()) vertex = stoi(fv);
        }
        if (std::getline(fvss, fv, '/')) {
            if (fv.length()) texture = stoi(fv);
        }
        if (std::getline(fvss, fv, '/')) {
            if (fv.length()) normal = stoi(fv);
        }

        struct FaceVertex face_vertex = { vertex, texture, normal };
        face_vertices.push_back(face_vertex);
    }

    return face_vertices;
}

Group* ObjParser::defaultGroup() {
    return m_groups[0]->toGroup(m_material);
}

Group* ObjParser::superGroup() {
    Group* super_group = new Group(m_material);
    for (auto &group : m_groups) {
        auto newGroup = group->toGroup(m_material);
        if (newGroup->size() > 0) {
            super_group->addShape(newGroup);
        }
    }

    return super_group;
}

Group* ObjParser::groupNamed(std::string name) {
    for (auto &group : m_groups) {
        if (name == group->name()) return group->toGroup(m_material);
    }

    assert(false);
    return defaultGroup();
}