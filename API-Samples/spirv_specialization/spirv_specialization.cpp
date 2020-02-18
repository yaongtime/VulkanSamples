/*
 * Vulkan Samples Kit
 *
 * Copyright (C) 2016 Valve Corporation
 * Copyright (C) 2016 Google, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
VULKAN_SAMPLE_SHORT_DESCRIPTION

This sample creates a mini-ubershader that changes its behavior
based on specialization constants provided at pipeline creation.
If no constants are specialized, the shaders will render the
LunarG cube.  If only the boolean is specified, it will render
a black cube.  If both boolean and color values are specified,
it will render the specified color (blue).

The SPIR-V path is included as an alternative to using a front end.
*/

#include <util_init.hpp>
#include <assert.h>
#include <string.h>
#include <cstdlib>
#include "cube_data.h"
#include "spirv-tools/libspirv.h"

static const bool use_SPIRV_asm = true;

const char *vertShaderText =
    "#version 400\n"
    "#extension GL_ARB_separate_shader_objects : enable\n"
    "#extension GL_ARB_shading_language_420pack : enable\n"
    "layout (std140, binding = 0) uniform buf {\n"
    "        mat4 mvp;\n"
    "} ubuf;\n"
    "layout (location = 0) in vec4 pos;\n"
    "layout (location = 1) in vec2 inTexCoords;\n"
    "layout (location = 0) out vec2 texcoord;\n"
    "void main() {\n"
    "   texcoord = inTexCoords;\n"
    "   gl_Position = ubuf.mvp * pos;\n"
    "}\n";

const char *fragShaderText =
    "#version 400\n"
    "#extension GL_ARB_separate_shader_objects : enable\n"
    "#extension GL_ARB_shading_language_420pack : enable\n"
    "layout (binding = 1) uniform sampler2D tex;\n"
    "layout (location = 0) in vec2 texcoord;\n"
    "layout (location = 0) out vec4 outColor;\n"
    "layout (constant_id = 5) const bool drawUserColor = false;\n"
    "layout (constant_id = 7) const float r = 0.0f;\n"
    "layout (constant_id = 8) const float g = 0.0f;\n"
    "layout (constant_id = 9) const float b = 0.0f;\n"
    "void main() {\n"
    "   if (drawUserColor)\n"
    "      outColor = vec4(r, g, b, 1.0);\n"
    "   else\n"
    "      outColor = textureLod(tex, texcoord, 0.0);\n"
    "}\n";

// clang-format off
// The following inline SPIR-V assembly was generated by running the following commands on Linux:
//     ./glslang/build/StandAlone/glslangValidator -V ./VulkanSamplesKit/nospec_specialization.frag -o ./VulkanSamplesKit/nospec_specialization.frag.spv
//     ./spirv-tools/build/spirv-dis ./VulkanSamplesKit/nospec_specialization.frag.spv | sed -e 's/\"/\\\"/g' -e 's/.*/\"&\\n\"/'

// This is the unmodified output from the above lines
const std::string fragmentSPIRV =
        "; SPIR-V\n"
        "; Version: 1.0\n"
        "; Generator: Khronos Glslang Reference Front End; 1\n"
        "; Bound: 29\n"
        "; Schema: 0\n"
        "               OpCapability Shader\n"
        "          %1 = OpExtInstImport \"GLSL.std.450\"\n"
        "               OpMemoryModel Logical GLSL450\n"
        "               OpEntryPoint Fragment %4 \"main\" %13 %25\n"
        "               OpExecutionMode %4 OriginUpperLeft\n"
        "               OpSource GLSL 400\n"
        "               OpSourceExtension \"GL_ARB_separate_shader_objects\"\n"
        "               OpSourceExtension \"GL_ARB_shading_language_420pack\"\n"
        "               OpName %4 \"main\"\n"
        "               OpName %13 \"outColor\"\n"
        "               OpName %21 \"tex\"\n"
        "               OpName %25 \"texcoord\"\n"
        "               OpDecorate %7 SpecId 5\n"
        "               OpDecorate %13 Location 0\n"
        "               OpDecorate %14 SpecId 7\n"
        "               OpDecorate %14 SpecId 8\n"
        "               OpDecorate %14 SpecId 9\n"
        "               OpDecorate %21 DescriptorSet 0\n"
        "               OpDecorate %21 Binding 1\n"
        "               OpDecorate %25 Location 0\n"
        "          %2 = OpTypeVoid\n"
        "          %3 = OpTypeFunction %2\n"
        "          %6 = OpTypeBool\n"
        "          %7 = OpSpecConstantFalse %6\n"
        "         %10 = OpTypeFloat 32\n"
        "         %11 = OpTypeVector %10 4\n"
        "         %12 = OpTypePointer Output %11\n"
        "         %13 = OpVariable %12 Output\n"
        "         %14 = OpSpecConstant %10 0\n"
        "         %15 = OpConstant %10 1\n"
        "         %18 = OpTypeImage %10 2D 0 0 0 1 Unknown\n"
        "         %19 = OpTypeSampledImage %18\n"
        "         %20 = OpTypePointer UniformConstant %19\n"
        "         %21 = OpVariable %20 UniformConstant\n"
        "         %23 = OpTypeVector %10 2\n"
        "         %24 = OpTypePointer Input %23\n"
        "         %25 = OpVariable %24 Input\n"
        "         %27 = OpConstant %10 0\n"
        "          %4 = OpFunction %2 None %3\n"
        "          %5 = OpLabel\n"
        "               OpSelectionMerge %9 None\n"
        "               OpBranchConditional %7 %8 %17\n"
        "          %8 = OpLabel\n"
        "         %16 = OpCompositeConstruct %11 %14 %14 %14 %15\n"
        "               OpStore %13 %16\n"
        "               OpBranch %9\n"
        "         %17 = OpLabel\n"
        "         %22 = OpLoad %19 %21\n"
        "         %26 = OpLoad %23 %25\n"
        "         %28 = OpImageSampleExplicitLod %11 %22 %26 Lod %27\n"
        "               OpStore %13 %28\n"
        "               OpBranch %9\n"
        "          %9 = OpLabel\n"
        "               OpReturn\n"
        "               OpFunctionEnd\n";

// This is the output with hand edits to enable specialization
const std::string fragmentSPIRV_specialized =
        "; SPIR-V\n"
        "; Version: 1.0\n"
        "; Generator: Khronos Glslang Reference Front End; 1\n"
        // Updated bound to reflect hand added variables
        "; Bound: 32\n"
        "; Schema: 0\n"
        "               OpCapability Shader\n"
        "          %1 = OpExtInstImport \"GLSL.std.450\"\n"
        "               OpMemoryModel Logical GLSL450\n"
        "               OpEntryPoint Fragment %4 \"main\" %13 %25\n"
        "               OpExecutionMode %4 OriginUpperLeft\n"
        "               OpSource GLSL 400\n"
        "               OpSourceExtension \"GL_ARB_separate_shader_objects\"\n"
        "               OpSourceExtension \"GL_ARB_shading_language_420pack\"\n"
        "               OpName %4 \"main\"\n"
        "               OpName %13 \"outColor\"\n"
        "               OpName %21 \"tex\"\n"
        "               OpName %25 \"texcoord\"\n"
        "               OpDecorate %7 SpecId 5\n"
        "               OpDecorate %13 Location 0\n"
        "               OpDecorate %14 SpecId 7\n"

        // Updated the spec constant decoration from %14 -> %29
        "               OpDecorate %29 SpecId 8\n"

        // Updated the spec constant decoration from %14 -> %30
        "               OpDecorate %30 SpecId 9\n"

        "               OpDecorate %21 DescriptorSet 0\n"
        "               OpDecorate %21 Binding 1\n"
        "               OpDecorate %25 Location 0\n"
        "          %2 = OpTypeVoid\n"
        "          %3 = OpTypeFunction %2\n"
        "          %6 = OpTypeBool\n"
        "          %7 = OpSpecConstantFalse %6\n"
        "         %10 = OpTypeFloat 32\n"
        "         %11 = OpTypeVector %10 4\n"
        "         %12 = OpTypePointer Output %11\n"
        "         %13 = OpVariable %12 Output\n"
        "         %14 = OpSpecConstant %10 0\n"

        // Add new spec constants
        "         %29 = OpSpecConstant %10 0.0\n"
        "         %30 = OpSpecConstant %10 0.0\n"

        // Uncomment the below to emulate the app's specialization
        //"         %7 = OpSpecConstantTrue %6\n"
        //"         %30 = OpSpecConstant %10 1.0\n"

        "         %15 = OpConstant %10 1\n"
        "         %18 = OpTypeImage %10 2D 0 0 0 1 Unknown\n"
        "         %19 = OpTypeSampledImage %18\n"
        "         %20 = OpTypePointer UniformConstant %19\n"
        "         %21 = OpVariable %20 UniformConstant\n"
        "         %23 = OpTypeVector %10 2\n"
        "         %24 = OpTypePointer Input %23\n"
        "         %25 = OpVariable %24 Input\n"
        "         %27 = OpConstant %10 0\n"
        "          %4 = OpFunction %2 None %3\n"
        "          %5 = OpLabel\n"
        "               OpSelectionMerge %9 None\n"
        "               OpBranchConditional %7 %8 %17\n"
        "          %8 = OpLabel\n"

        // Consume the color spec_constants  %14 -> %29, %14 -> %30
        "         %16 = OpCompositeConstruct %11 %14 %29 %30 %15\n"

        "               OpStore %13 %16\n"
        "               OpBranch %9\n"
        "         %17 = OpLabel\n"
        "         %22 = OpLoad %19 %21\n"
        "         %26 = OpLoad %23 %25\n"
        "         %28 = OpImageSampleExplicitLod %11 %22 %26 Lod %27\n"
        "               OpStore %13 %28\n"
        "               OpBranch %9\n"
        "          %9 = OpLabel\n"
        "               OpReturn\n"
        "               OpFunctionEnd\n";
// clang-format on

int sample_main(int argc, char *argv[]) {
    VkResult U_ASSERT_ONLY res;
    struct sample_info info = {};
    char sample_title[] = "SPIR-V Specialization";
    const bool depthPresent = true;

    process_command_line_args(info, argc, argv);
    init_global_layer_properties(info);
    init_instance_extension_names(info);
    init_device_extension_names(info);
    init_instance(info, sample_title);
    init_enumerate_device(info);
    init_window_size(info, 500, 500);
    init_connection(info);
    init_window(info);
    init_swapchain_extension(info);
    init_device(info);
    init_command_pool(info);
    init_command_buffer(info);
    execute_begin_command_buffer(info);
    init_device_queue(info);
    init_swap_chain(info);
    init_depth_buffer(info);
    init_texture(info);
    init_uniform_buffer(info);
    init_descriptor_and_pipeline_layouts(info, true);
    init_renderpass(info, depthPresent);

    /* VULKAN_KEY_START */

    // Pass in nullptr for fragment shader so we can setup specialization
    init_shaders(info, vertShaderText, nullptr);

    // This structure maps constant ids to data locations.
    // NOTE: Padding bool to 32-bits for simplicity
    const VkSpecializationMapEntry entries[] =
        // id,  offset,                size
        {{5, 0, sizeof(uint32_t)},
         {7, 1 * sizeof(uint32_t), sizeof(uint32_t)},
         {8, 2 * sizeof(uint32_t), sizeof(uint32_t)},
         {9, 3 * sizeof(uint32_t), sizeof(uint32_t)}};

    // Initialize the values we want our mini-ubershader to use
    const bool drawUserColor = true;
    const float userColor[] = {0.0f, 0.0f, 1.0f};

    // Populate our data entry
    uint32_t data[4] = {};
    data[0] = drawUserColor ? 1 : 0;
    ((float *)data)[1] = userColor[0];
    ((float *)data)[2] = userColor[1];
    ((float *)data)[3] = userColor[2];

    // Set up the info describing our spec map and data
    const VkSpecializationInfo specInfo = {
        4,                  // mapEntryCount
        entries,            // pMapEntries
        4 * sizeof(float),  // dataSize
        data,               // pData
    };

    // Provide the specialization data to fragment stage
    info.shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    info.shaderStages[1].pNext = NULL;
    info.shaderStages[1].pSpecializationInfo = &specInfo;
    info.shaderStages[1].flags = 0;
    info.shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    info.shaderStages[1].pName = "main";

    VkShaderModuleCreateInfo moduleCreateInfo;
    moduleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    moduleCreateInfo.pNext = NULL;
    moduleCreateInfo.flags = 0;

    if (use_SPIRV_asm) {
        // Use the hand edited SPIR-V assembly
        spv_context spvContext = spvContextCreate(SPV_ENV_VULKAN_1_0);
        spv_binary fragmentBinary = {};
        spv_diagnostic fragmentDiag = {};
        spv_result_t U_ASSERT_ONLY fragmentResult = spvTextToBinary(
            spvContext, fragmentSPIRV_specialized.c_str(), fragmentSPIRV_specialized.length(), &fragmentBinary, &fragmentDiag);
        if (fragmentDiag) {
            printf("Diagnostic info from fragment shader:\n");
            spvDiagnosticPrint(fragmentDiag);
        }
        assert(fragmentResult == SPV_SUCCESS);
        moduleCreateInfo.codeSize = fragmentBinary->wordCount * sizeof(unsigned int);
        moduleCreateInfo.pCode = fragmentBinary->code;
        spvDiagnosticDestroy(fragmentDiag);
        spvContextDestroy(spvContext);

    } else {
        // Convert GLSL to SPIR-V
        init_glslang();
        std::vector<unsigned int> fragSpv;
        bool U_ASSERT_ONLY retVal = GLSLtoSPV(VK_SHADER_STAGE_FRAGMENT_BIT, fragShaderText, fragSpv);
        assert(retVal);
        finalize_glslang();

        moduleCreateInfo.codeSize = fragSpv.size() * sizeof(unsigned int);
        moduleCreateInfo.pCode = fragSpv.data();
    }

    res = vkCreateShaderModule(info.device, &moduleCreateInfo, NULL, &info.shaderStages[1].module);
    assert(res == VK_SUCCESS);

    /* VULKAN_KEY_END */

    init_framebuffers(info, depthPresent);
    init_vertex_buffer(info, g_vb_texture_Data, sizeof(g_vb_texture_Data), sizeof(g_vb_texture_Data[0]), true);
    init_descriptor_pool(info, true);
    init_descriptor_set(info, true);
    init_pipeline_cache(info);
    init_pipeline(info, depthPresent);
    init_presentable_image(info);

    VkClearValue clear_values[2];
    init_clear_color_and_depth(info, clear_values);

    VkRenderPassBeginInfo rp_begin;
    init_render_pass_begin_info(info, rp_begin);
    rp_begin.clearValueCount = 2;
    rp_begin.pClearValues = clear_values;

    vkCmdBeginRenderPass(info.cmd, &rp_begin, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(info.cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, info.pipeline);
    vkCmdBindDescriptorSets(info.cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, info.pipeline_layout, 0, NUM_DESCRIPTOR_SETS,
                            info.desc_set.data(), 0, NULL);

    const VkDeviceSize offsets[1] = {0};
    vkCmdBindVertexBuffers(info.cmd, 0, 1, &info.vertex_buffer.buf, offsets);

    init_viewports(info);
    init_scissors(info);

    vkCmdDraw(info.cmd, 12 * 3, 1, 0, 0);
    vkCmdEndRenderPass(info.cmd);
    res = vkEndCommandBuffer(info.cmd);
    assert(res == VK_SUCCESS);

    VkFence drawFence = {};
    init_fence(info, drawFence);
    VkPipelineStageFlags pipe_stage_flags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    VkSubmitInfo submit_info = {};
    init_submit_info(info, submit_info, pipe_stage_flags);

    /* Queue the command buffer for execution */
    res = vkQueueSubmit(info.graphics_queue, 1, &submit_info, drawFence);
    assert(res == VK_SUCCESS);

    /* Now present the image in the window */
    VkPresentInfoKHR present = {};
    init_present_info(info, present);

    /* Make sure command buffer is finished before presenting */
    do {
        res = vkWaitForFences(info.device, 1, &drawFence, VK_TRUE, FENCE_TIMEOUT);
    } while (res == VK_TIMEOUT);
    assert(res == VK_SUCCESS);
    res = vkQueuePresentKHR(info.present_queue, &present);
    assert(res == VK_SUCCESS);

    wait_seconds(1);
    if (info.save_images) write_ppm(info, "spirv_specialization");

    vkDestroyFence(info.device, drawFence, NULL);
    vkDestroySemaphore(info.device, info.imageAcquiredSemaphore, NULL);
    destroy_pipeline(info);
    destroy_pipeline_cache(info);
    destroy_textures(info);
    destroy_descriptor_pool(info);
    destroy_vertex_buffer(info);
    destroy_framebuffers(info);
    destroy_shaders(info);
    destroy_renderpass(info);
    destroy_descriptor_and_pipeline_layouts(info);
    destroy_uniform_buffer(info);
    destroy_depth_buffer(info);
    destroy_swap_chain(info);
    destroy_command_buffer(info);
    destroy_command_pool(info);
    destroy_device(info);
    destroy_window(info);
    destroy_instance(info);
    return 0;
}
