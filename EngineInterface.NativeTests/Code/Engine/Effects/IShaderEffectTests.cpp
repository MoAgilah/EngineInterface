#include "CppUnitTest.h"

#include <Fakes/Resources/FakeShader.h>
#include <Fakes/Effects/FakeShaderEffect.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Engine
{
    namespace Effects
    {
        TEST_CLASS(IShaderEffectTests)
        {
        public:
            TEST_METHOD(IShaderEffect_Constructor_ThrowsIfShaderIsNull)
            {
                Assert::ExpectException<std::invalid_argument>(
                    []()
                    {
                        FakeShaderEffect shaderEffect(nullptr);
                    });
            }

            TEST_METHOD(IShaderEffect_Constructor_StoresShader)
            {
                FakeShader shader;
                FakeShaderEffect shaderEffect(&shader);

                IShader* expected = &shader;
                IShader* actual = shaderEffect.GetShader();

                Assert::IsTrue(expected == actual);
            }
        };
    }
}