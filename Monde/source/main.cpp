#include <iostream>
#include <imgui.h>
#include <glm/glm.hpp>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <Window.hpp>

int main() {
	Window window;
	auto* w = window.getWindow();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO &io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_IsTouchScreen;

	ImGui_ImplGlfw_InitForOpenGL(w, true);
	ImGui_ImplOpenGL3_Init();

	window.createShaderProgram();

	window.test();

	while (!glfwWindowShouldClose(w)) {
		glfwPollEvents();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		window.loop();

		ImGui::ShowDemoWindow();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(w);
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}