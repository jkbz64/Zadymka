Zadymka = require("Zadymka")
Graphics = Zadymka.Graphics

describe("Graphics module", function()
    it("Graphics' module init works", function()
        assert.is_true(Graphics.init())
    end)

    it("Graphics' usertypes are not nil", function()
        assert.is_not_nil(Graphics.init)
        assert.is_not_nil(Graphics.deinit)
        assert.is_not_nil(Graphics.Window)
        assert.is_not_nil(Graphics.RenderTexture)
        assert.is_not_nil(Graphics.Camera)
        assert.is_not_nil(Graphics.Texture)
        assert.is_not_nil(Graphics.Shader)
        assert.is_not_nil(Graphics.Drawable)
        assert.is_not_nil(Graphics.Rectangle)
        assert.is_not_nil(Graphics.Sprite)
        assert.is_not_nil(Graphics.Font)
        assert.is_not_nil(Graphics.Text)
        assert.is_not_nil(Graphics.VertexArray)
    end)

    describe("Window", function()
        local window
        it("Window::Window()", function()
            assert.has_no_errors(function() window = Graphics.Window:new() end)
        end)
        it("Window::create", function()
            assert.has_no_errors(function() window:create(100, 100, 'Test', Graphics.WindowStyle.Windowed) end)
            assert.has_errors(function() window:create(0, 100, 'Test', Graphics.WindowStyle.Windowed) end)
        end)
    end)

    describe("Shader class", function()
        local shader
        it("Shader::Shader()", function()
            assert.has_no_errors(function() shader = Graphics.Shader:new() end)
        end)

        before_each(function()
            shader = Graphics.Shader:new()
        end)

        it("Shader::loadFromMemory", function()
            assert.is_true(shader:loadFromMemory([[
                #version 330 core
                layout ( location = 0 ) in vec2 vertex;
                uniform mat4 mvp;
                void main()
                {
                    gl_Position = mvp * vec4(vertex.xy, 0.0, 1.0);
                }
                ]],
                [[
                #version 330 core
                out vec4 FragColor;
                uniform vec4 color;
                void main()
                {
                    FragColor = color;
                }
                ]]))
            assert.is_true(shader:isLoaded())
        end)

        it("Shader::loadFromFile", function()
            assert.is_true(shader:loadFromFile('test.vs', 'test.fs'))
            assert.is_true(shader:isLoaded())
        end)
    end)

    describe("RenderTexture class", function()
        local renderTexture
        it("Checks constructor validity", function()
            assert.has_no_errors(function() renderTexture = Graphics.RenderTexture:new() end)
        end)
        it("RenderTexture::create", function()
            assert.has_no_errors(function() renderTexture:create(100, 100) end)
        end)
    end)




    it("Graphics' module deinit works", function()
        assert.has_no_errors(function() Graphics.deinit() end)
    end)
end)