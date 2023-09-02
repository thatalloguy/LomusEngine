#pragma once
#include "DebugVAO.h"
#include "DebugVBO.h"
#include "../Shader/ShaderClass.h"
#include <reactphysics3d/reactphysics3d.h> 
#include "../Renderer/Camera.h"
#include <iostream>
using namespace reactphysics3d;

namespace Lomus {

	class DebugRenderer {

	public:

		DebugRenderer(PhysicsWorld* world) {

			//Init The Vbo and VAO for lines :)
			// translated: VBO *inits* VAO *creates and inits* VBO *bind it so vao reconginze it*
			mDebugLinesVBO.create();

			mDebugLinesVAO.create();
			mDebugLinesVAO.bind();

			mDebugLinesVBO.bind();

			mDebugLinesVAO.unbind();

			mDebugLinesVBO.unbind();

			//Now do the same for triangles

			mDebugTrianglesVBO.create();

			mDebugTrianglesVAO.create();
			mDebugTrianglesVAO.bind();

			mDebugTrianglesVBO.bind();

			mDebugTrianglesVAO.unbind();

			mDebugTrianglesVBO.unbind();

			world->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLIDER_AABB, true);
			world->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
			world->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::CONTACT_POINT, true);
			world->setIsDebugRenderingEnabled(true);
		};

		void Render(PhysicsWorld* world, Camera& camera) {
			updateBuffers(world);

			reactphysics3d::DebugRenderer& debugRenderer = world->getDebugRenderer();

			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			debugShader.Activate();
			camera.Matrix(debugShader, "camMatrix");

			debugShader.setIntUniform("useGlobalVertexColor", 0);

			GLuint vertexPositionLoc = debugShader.getUniformLocation("aPos");
			GLuint vertexColorLoc = debugShader.getUniformLocation("vertexColor");

			// line TIME
			std::cout << "L: " << debugRenderer.getNbLines() << "\n";
			std::cout << "T: " << debugRenderer.getNbTriangles() << "\n";
			std::cout << "r: " << world->getIsDebugRenderingEnabled() << "\n";
			
			if (debugRenderer.getNbLines() > 0) {
				std::cout << "rendering shit rn\n";
				mDebugLinesVAO.bind();

				mDebugLinesVBO.bind();

				glEnableVertexAttribArray(vertexPositionLoc);
				glVertexAttribPointer(vertexPositionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*)nullptr);

				glEnableVertexAttribArray(vertexColorLoc);
				glVertexAttribIPointer(vertexColorLoc, 3, GL_UNSIGNED_INT, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (void*)sizeof(rp3d::Vector3));


				glDrawArrays(GL_LINES, 0, debugRenderer.getNbLines() * 2);

				glDisableVertexAttribArray(vertexPositionLoc);
				glDisableVertexAttribArray(vertexColorLoc);

				mDebugLinesVBO.unbind();

				mDebugLinesVAO.unbind();

			}

			if (debugRenderer.getNbTriangles() > 0) {
				std::cout << "rendering shit rn\n";
				// Bind the VAO
				mDebugTrianglesVAO.bind();

				mDebugTrianglesVBO.bind();

				glEnableVertexAttribArray(vertexPositionLoc);
				glVertexAttribPointer(vertexPositionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (char*)nullptr);

				glEnableVertexAttribArray(vertexColorLoc);
				glVertexAttribIPointer(vertexColorLoc, 3, GL_UNSIGNED_INT, sizeof(rp3d::Vector3) + sizeof(rp3d::uint32), (void*)sizeof(rp3d::Vector3));

				// Draw the triangles geometry
				glDrawArrays(GL_TRIANGLES, 0, debugRenderer.getNbTriangles() * 3);

				glDisableVertexAttribArray(vertexPositionLoc);
				glDisableVertexAttribArray(vertexColorLoc);

				mDebugTrianglesVBO.unbind();

				// Unbind the VAO
				mDebugTrianglesVAO.unbind();
			}

			debugShader.Deactivate();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		};

		void Delete() {
			mDebugLinesVBO.destroy();
			mDebugLinesVAO.Delete();
			mDebugTrianglesVAO.Delete();
			mDebugTrianglesVBO.destroy();

			debugShader.Delete();
		};

	private:

		void updateBuffers(PhysicsWorld* world) {
			reactphysics3d::DebugRenderer& debugRenderer = world->getDebugRenderer();

			// --- Lines --- //
			const uint nbLines = debugRenderer.getNbLines();

			if (nbLines > 0) {
				mDebugLinesVBO.bind();
				GLsizei sizeVertices = static_cast<GLsizei>(nbLines * sizeof(reactphysics3d::DebugRenderer::DebugLine));
				mDebugLinesVBO.copyDataIntoVBO(sizeVertices, debugRenderer.getLinesArray(), GL_STREAM_DRAW);
				mDebugLinesVBO.unbind();

			}

			// -- Triangles -- //
			const uint nbTriangles = debugRenderer.getNbTriangles();

			if (nbTriangles > 0) {
				mDebugTrianglesVBO.bind();
				GLsizei sizeVertices = static_cast<GLsizei>(nbTriangles * sizeof(reactphysics3d::DebugRenderer::DebugTriangle));
				mDebugTrianglesVBO.copyDataIntoVBO(sizeVertices, debugRenderer.getTrianglesArray(), GL_STREAM_DRAW);
				mDebugTrianglesVBO.unbind();
			}
		};

		DebugVAO mDebugLinesVAO{};
		DebugVAO mDebugTrianglesVAO{};

		DebugVBO mDebugLinesVBO{};
		DebugVBO mDebugTrianglesVBO{};

		Shader debugShader{ "../../../Lomus/Shader/shaders/debug.vert", "../../../Lomus/Shader/shaders/debug.frag" };
	};

};

