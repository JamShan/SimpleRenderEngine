#pragma once

#include "glm/glm.hpp"
#include <vector>
#include <array>
#include "sre/MeshTopology.hpp"

#include "sre/impl/Export.hpp"

namespace sre {
    /**
     * Represents a Mesh object.
     * A mesh is composed of a list of
     * - vertexPositions (vec3)
     * - normals (vec3)
     * - uvs (aka. texture coordinates) (vec2)
     *
     * A mesh also has a meshType, which can be either: MeshTopology::Points, MeshTopology::Lines, or MeshTopology::Triangles
     */
    class DllExport Mesh {
    public:
        class DllExport MeshBuilder {
        public:
            MeshBuilder& withSphere();
            MeshBuilder& withCube();
            MeshBuilder& withQuad();
            MeshBuilder& withVertexPositions(const std::vector<glm::vec3> &vertexPositions);
            MeshBuilder& withNormals(const std::vector<glm::vec3> &normals);
            MeshBuilder& withUvs(const std::vector<glm::vec4> &uvs);
            MeshBuilder& withColors(const std::vector<glm::vec4> &colors);
            MeshBuilder& withParticleSize(const std::vector<float> &particleSize);
            MeshBuilder& withMeshTopology(MeshTopology meshTopology);
            MeshBuilder& withIndices(const std::vector<uint16_t> &indices);
            Mesh* build();
        private:
            MeshBuilder() = default;
            std::vector<glm::vec3> vertexPositions;
            std::vector<glm::vec3> normals;
            std::vector<glm::vec4> uvs;
            std::vector<glm::vec4> colors;
            std::vector<float> particleSize;
            MeshTopology meshTopology = MeshTopology::Triangles;
            std::vector<uint16_t> indices;
            Mesh* updateMesh = nullptr;
            friend class Mesh;
        };
        ~Mesh();

        static MeshBuilder create();
        MeshBuilder update();

        int getVertexCount();
        MeshTopology getMeshTopology();

        const std::vector<glm::vec3>& getVertexPositions();
        const std::vector<glm::vec3>& getNormals();
        const std::vector<glm::vec4>& getUVs();
        const std::vector<glm::vec4>& getColors();
        const std::vector<float>& getParticleSize();
        const std::vector<uint16_t>& getIndices();

        // get the local axis aligned bounding box
        std::array<glm::vec3,2> getBoundsMinMax();

        // get size of the mesh in bytes on GPU
        int getDataSize();
    private:
        Mesh(const std::vector<glm::vec3> &vertexPositions, const std::vector<glm::vec3> &normals, const std::vector<glm::vec4> &uvs, const std::vector<glm::vec4> &colors,std::vector<float> particleSize, const std::vector<uint16_t> &indices, MeshTopology meshTopology);
        void update(const std::vector<glm::vec3> &vertexPositions, const std::vector<glm::vec3> &normals, const std::vector<glm::vec4> &uvs, const std::vector<glm::vec4> &colors, std::vector<float> particleSize, const std::vector<uint16_t> &indices, MeshTopology meshTopology);

        void setVertexAttributePointers();
        MeshTopology meshTopology;
        unsigned int vertexBufferId;
        unsigned int vertexArrayObject;
        unsigned int elementBufferId;
        int vertexCount;

        std::vector<glm::vec3> vertexPositions;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec4> uvs;
        std::vector<float> particleSize;
        std::vector<glm::vec4> colors;
        std::vector<uint16_t> indices;

        std::array<glm::vec3,2> boundsMinMax;

        void bind();

        friend class RenderPass;
    };
}