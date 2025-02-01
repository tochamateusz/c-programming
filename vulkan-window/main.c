
#include <GLFW/glfw3.h>
#define GLFW_INCLUDE_VULKAN // Include Vulkan headers with GLFW

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototypes
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

// Error callback for GLFW
void glfwErrorCallback(int error, const char *description) {
  fprintf(stderr, "GLFW Error (%d): %s\n", error, description);
}

int main(void) {
  // Initialize GLFW
  glfwSetErrorCallback(glfwErrorCallback); // Set the error callback
  if (!glfwInit()) {
    fprintf(stderr, "Failed to initialize GLFW\n");
    return -1;
  }

  // Tell GLFW to not create an OpenGL context and to use Vulkan
  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  // Create the GLFW window
  GLFWwindow *window = glfwCreateWindow(800, 600, "Vulkan Window", NULL, NULL);
  if (!window) {
    fprintf(stderr, "Failed to create GLFW window\n");
    glfwTerminate();
    return -1;
  }

  // Set the framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Create Vulkan instance
  VkInstance instance;
  VkApplicationInfo appInfo = {};
  appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
  appInfo.pApplicationName = "Vulkan Window";
  appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.pEngineName = "No Engine";
  appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
  appInfo.apiVersion = VK_API_VERSION_1_0;

  VkInstanceCreateInfo createInfo = {};
  createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
  createInfo.pApplicationInfo = &appInfo;

  // Get GLFW required extensions for Vulkan
  uint32_t glfwExtensionCount = 0;
  const char **glfwExtensions =
      glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
  createInfo.enabledExtensionCount = glfwExtensionCount;
  createInfo.ppEnabledExtensionNames = glfwExtensions;

  // Create Vulkan instance
  if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS) {
    fprintf(stderr, "Failed to create Vulkan instance\n");
    return -1;
  }

  // Create a Vulkan surface
  VkSurfaceKHR surface;
  if (glfwCreateWindowSurface(instance, window, NULL, &surface) != VK_SUCCESS) {
    fprintf(stderr, "Failed to create Vulkan surface\n");
    return -1;
  }

  // Main event loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    // Here you'd submit rendering commands to Vulkan
  }

  // Cleanup
  vkDestroySurfaceKHR(instance, surface, NULL);
  vkDestroyInstance(instance, NULL);
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}

// Handle window resizing (in Vulkan, resizing needs special handling)
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  printf("Window resized: %dx%d\n", width, height);
  // In Vulkan, you'll need to recreate the swapchain here
}
