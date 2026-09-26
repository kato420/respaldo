return {
  {
    "akinsho/toggleterm.nvim",
    version = "*",
    config = function()
      require("toggleterm").setup({
        size = 20,
        open_mapping = [[<c-p>]], -- Atajo global para abrir/cerrar
        direction = "float", -- Aquí forzamos que sea flotante
        float_opts = {
          border = "curved", -- Se ve más elegante en Arch
        },
      })
    end,
  },
  {
    "sphamba/smear-cursor.nvim",
    opts = {},
  },
  {
    "folke/tokyonight.nvim",
    opts = {
      transparent = true,
      styles = {
        sidebars = "transparent",
        floats = "transparent",
      },
    },
  },
  {
    "folke/noice.nvim",
    opts = function(_, opts)
      table.insert(opts.routes, {
        filter = {
          event = "notify",
          find = "No information available",
        },
        opts = { skip = true },
      })
      opts.presets.lsp_doc_border = true
    end,
  },
  { "folke/flash.nvim", enabled = false },
}
