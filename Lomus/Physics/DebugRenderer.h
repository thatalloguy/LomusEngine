#pragma once

#include "../Shader/ShaderClass.h"
#include "../Renderer/Camera.h"
#include "../Core/SceneManager.h"
#include "DebugVAO.h"
#include "DebugVBO.h"

#include <reactphysics3d/reactphysics3d.h>
#include <iostream>

using namespace reactphysics3d;



namespace Lomus {
	struct debugVertex {
		float x;
		float y;
		float z;
	};

    struct debugShape{
        std::vector<debugVertex> vertices;
        std::vector<int> indices;
    };

	class DRay {

	public:

        DRay(PhysicsWorld* world) {

			//Init The Vbo and VAO for lines :)
			// translated: VBO *inits* VAO *creates and inits* VBO *bind it so vao reconginze it*

			//Now do the same for triangles

			mDebugTrianglesVBO.create();
			mDebugTrianglesVAO.create();

			mDebugTrianglesVAO.bind();

			mDebugTrianglesVBO.bind();


			mDebugTrianglesVAO.unbind();

			mDebugTrianglesVBO.unbind();


			world->getDebugRenderer().setIsDebugItemDisplayed(reactphysics3d::DebugRenderer::DebugItem::COLLISION_SHAPE, true);
			world->setIsDebugRenderingEnabled(true);


            updateBuffers(world);

        };

		void Render(PhysicsWorld* world, Camera& camera, bool update) {


			reactphysics3d::DebugRenderer& debugRenderer = world->getDebugRenderer();
            debugRenderer.reset();
			debugRenderer.computeDebugRenderingPrimitives(*world);


            updateBuffers(world);



			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			debugShader.Activate();
			camera.Matrix(debugShader, "camMatrix");

			debugShader.setIntUniform("useGlobalVertexColor", 0);

			GLuint vertexPositionLoc = glGetUniformLocation(debugShader.ID, "aPos");//debugShader.getUniformLocation("aPos");
			GLuint vertexColorLoc = glGetUniformLocation(debugShader.ID, "camMatrix");

			if (debugRenderer.getNbTriangles() > 0) {
				// Bind the VAO
				mDebugTrianglesVAO.bind();

				mDebugTrianglesVBO.bind();
                GLenum glError;

				glEnableVertexAttribArray(vertexPositionLoc);
				glVertexAttribPointer(vertexPositionLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Lomus::debugVertex), (void*) 0);

				glEnableVertexAttribArray(vertexColorLoc);
				glVertexAttribIPointer(vertexColorLoc, 3, GL_UNSIGNED_INT, sizeof(Lomus::debugVertex), (void*)sizeof(Lomus::debugVertex));



				// Draw the triangles geometry
				glDrawArrays(GL_TRIANGLES, 0, newVertices.size());


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
			mDebugTrianglesVAO.Delete();
			mDebugTrianglesVBO.destroy();

			debugShader.Delete();
		};

        void addCustomDebugShape(debugShape& shape) {

        }


	private:



		void updateBuffers(PhysicsWorld* world) {

			reactphysics3d::DebugRenderer& debugRenderer = world->getDebugRenderer();


            // -- Triangles -- //
			const uint nbTriangles = debugRenderer.getNbTriangles();

			if (nbTriangles > 0) {
				mDebugTrianglesVBO.bind();

                rp3d::Array<rp3d::DebugRenderer::DebugTriangle> rawTriangles = debugRenderer.getTriangles();



                newVertices.clear();
				for (int i = 0; i < nbTriangles; i++) {
					newVertices.push_back(Lomus::debugVertex{ -rawTriangles[i].point1.x, rawTriangles[i].point1.y, -rawTriangles[i].point1.z });
					newVertices.push_back(Lomus::debugVertex{ -rawTriangles[i].point2.x, rawTriangles[i].point2.y, -rawTriangles[i].point2.z });
					newVertices.push_back(Lomus::debugVertex{ -rawTriangles[i].point3.x, rawTriangles[i].point3.y, -rawTriangles[i].point3.z });
				}


				mDebugTrianglesVBO.copyDataIntoVBO(newVertices.size() * sizeof(Lomus::debugVertex), newVertices.data(), GL_DYNAMIC_DRAW);
				mDebugTrianglesVBO.unbind();

			}



        }


		DebugVAO mDebugTrianglesVAO{};
		DebugVBO mDebugTrianglesVBO{};


        std::vector<Lomus::debugVertex> newVertices;
        uint oldNbTriangles = 0;
        bool isfirst = true;

		Shader debugShader{ "../../Lomus/Shader/shaders/debug.vert", "../../Lomus/Shader/shaders/debug.frag" };
	};

};

