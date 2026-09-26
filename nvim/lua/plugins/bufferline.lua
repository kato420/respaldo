return {
  "akinsho/bufferline.nvim",
  opts = function(_, opts)
    local transparent = { bg = "none" }
    local hl_keys = {
      "fill",
      "background",
      "tab",
      "tab_selected",
      "tab_close",
      "close_button",
      "close_button_visible",
      "close_button_selected",
      "buffer_visible",
      "buffer_selected",
      "numbers",
      "numbers_visible",
      "numbers_selected",
      "diagnostic",
      "diagnostic_visible",
      "diagnostic_selected",
      "hint",
      "hint_visible",
      "hint_selected",
      "hint_diagnostic",
      "hint_diagnostic_visible",
      "hint_diagnostic_selected",
      "info",
      "info_visible",
      "info_selected",
      "info_diagnostic",
      "info_diagnostic_visible",
      "info_diagnostic_selected",
      "warning",
      "warning_visible",
      "warning_selected",
      "warning_diagnostic",
      "warning_diagnostic_visible",
      "warning_diagnostic_selected",
      "error",
      "error_visible",
      "error_selected",
      "error_diagnostic",
      "error_diagnostic_visible",
      "error_diagnostic_selected",
      "modified",
      "modified_visible",
      "modified_selected",
      "duplicate_selected",
      "duplicate_visible",
      "duplicate",
      "separator",
      "separator_selected",
      "separator_visible",
      "indicator_visible",
      "indicator_selected",
      "pick_selected",
      "pick_visible",
      "pick",
      "offset_separator",
      "trunc_marker",
    }

    opts.highlights = opts.highlights or {}
    for _, key in ipairs(hl_keys) do
      opts.highlights[key] = vim.tbl_extend("force", opts.highlights[key] or {}, transparent)
    end

    -- Asegurar que los grupos base de tabline en Neovim se mantengan transparentes
    local function set_transparent_tabline()
      vim.api.nvim_set_hl(0, "TabLineFill", { bg = "none" })
      vim.api.nvim_set_hl(0, "TabLine", { bg = "none" })
    end

    set_transparent_tabline()

    vim.api.nvim_create_autocmd("ColorScheme", {
      callback = set_transparent_tabline,
    })

    return opts
  end,
}
