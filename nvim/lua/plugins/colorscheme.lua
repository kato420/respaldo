return {
  {
    "lukas-reineke/indent-blankline.nvim",
    event = "LazyFile",
    opts = function()
      -- 1. Definir los nombres de los grupos de resaltado
      local highlight = {
        "RainbowRed",
        "RainbowYellow",
        "RainbowBlue",
        "RainbowOrange",
        "RainbowGreen",
        "RainbowViolet",
        "RainbowCyan",
      }

      -- 2. Registrar el hook para crear los colores
      -- 2. Registrar el hook para crear los colores (Versión Everforest)
      local hooks = require("ibl.hooks")
      hooks.register(hooks.type.HIGHLIGHT_SETUP, function()
        vim.api.nvim_set_hl(0, "RainbowRed", { fg = "#e67e80" })
        vim.api.nvim_set_hl(0, "RainbowYellow", { fg = "#dbbc7f" })
        vim.api.nvim_set_hl(0, "RainbowBlue", { fg = "#7fbbb3" }) -- El azul de Everforest tiende al aqua/teal
        vim.api.nvim_set_hl(0, "RainbowOrange", { fg = "#e69875" })
        vim.api.nvim_set_hl(0, "RainbowGreen", { fg = "#a7c080" })
        vim.api.nvim_set_hl(0, "RainbowViolet", { fg = "#d699b6" })
        vim.api.nvim_set_hl(0, "RainbowCyan", { fg = "#83c092" })
      end)

      -- 3. Retornar la configuración para que LazyVim la aplique
      return {
        indent = {
          highlight = highlight,
          char = "│", -- Puedes cambiar el carácter aquí
        },
        scope = { enabled = false }, -- Opcional: deshabilita el resaltado de scope si prefieres solo arcoíris
      }
    end,
    config = function(_, opts)
      -- Ejecutar el setup original con nuestras opciones
      require("ibl").setup(opts)
    end,
  },
  -- {
  --   "rose-pine/neovim",
  --   name = "rose-pine",
  --   config = function()
  --     require("rose-pine").setup({
  --       styles = {
  --         bold = true,
  --         italic = false,
  --         transparency = true,
  --       },
  --     })
  --     vim.cmd("colorscheme rose-pine")
  --   end,
  -- },
  -- Or with configuration
  -- {
  --   "sainnhe/sonokai",
  --   priority = 1000,
  --   config = function()
  --     vim.g.sonokai_transparent_background = "1"
  --     -- vim.g.sonokai_enable_italic = "1"
  --     vim.g.sonokai_style = "andromeda"
  --     vim.g.sonokai_float_style = "blend"
  --     vim.cmd.colorscheme("sonokai")
  --
  --     -- Hacer transparentes los popups y menús flotantes (WhichKey, Noice, Pmenu, etc.)
  --     local function set_floating_transparency()
  --       local transparent_groups = {
  --         "NormalFloat",
  --         "FloatBorder",
  --         "FloatTitle",
  --         "Pmenu",
  --         "PmenuKind",
  --         "PmenuExtra",
  --         "PmenuSbar",
  --       }
  --
  --       for _, group in ipairs(transparent_groups) do
  --         local hl = vim.api.nvim_get_hl(0, { name = group })
  --         vim.api.nvim_set_hl(0, group, vim.tbl_extend("force", hl, { bg = "none", ctermbg = "none" }))
  --       end
  --     end
  --
  --     set_floating_transparency()
  --
  --     vim.api.nvim_create_autocmd("ColorScheme", {
  --       callback = set_floating_transparency,
  --     })
  --   end,
  -- },
  {
    "marko-cerovac/material.nvim",
    init = function()
      vim.g.material_style = "darker" -- Otras opciones: 'ocean', 'palenight'
    end,
  },
  {
    "LazyVim/LazyVim",
    opts = {
      colorscheme = "material",
    },
  },
}
