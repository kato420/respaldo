-- Keymaps are automatically loaded on the VeryLazy event
-- Default keymaps that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/keymaps.lua
-- Add any additional keymaps here
-- Keymaps are automatically loaded on the VeryLazy event
-- Default keymaps that are always set: https://github.com/LazyVim/LazyVim/blob/main/lua/lazyvim/config/keymaps.lua
-- Add any additional keymaps here
-- Función para compilar y ejecutar el proyecto actual
local keymap = vim.keymap
local opts = { noremap = true, silent = true }
--
-- local function run_cpp_project()
--   -- 1. Guarda el archivo actual silenciosamente
--   vim.cmd("silent! write")
--
--   -- 2. Ejecuta el script ./run en ToggleTerm
--   -- 'direction=float' asegura que use la terminal flotante
--   vim.cmd('TermExec cmd="./run" direction=float')
-- end
--
-- -- 3. Mapear la tecla F5 en modo Normal
-- vim.keymap.set("n", "<F5>", run_cpp_project, { desc = "Compile and Run with Ninja" })

keymap.set("n", "<tab>", ":BufferLineCycleNext<Return>", opts)
keymap.set("n", "<s-tab>", ":BufferLineCyclePrev<Return>", opts)

-- -- runner ajustado para que la gráfica no se cierre
-- local function smart_run_project()
--   vim.cmd("silent! write")
--
--   local ft = vim.bo.filetype
--   local command = ""
--
--   if ft == "cpp" then
--     command = "./run"
--   elseif ft == "octave" or ft == "matlab" then
--     -- Usamos '--persist' para que Octave NO se salga al terminar.
--     -- Esto mantiene la ventana del gráfico abierta y te deja en el prompt de Octave.
--     command = "export QT_QPA_PLATFORM=xcb && clear && octave --persist " .. vim.fn.expand("%")
--   else
--     vim.notify("No hay un comando configurado para el tipo de archivo: " .. ft, vim.log.levels.WARN)
--     return
--   end
--
--   vim.cmd('TermExec cmd="' .. command .. '" direction=float')
-- end
--
-- -- El mapeo de la tecla F5 se mantiene igual
-- vim.keymap.set("n", "<F5>", smart_run_project, { desc = "Run Project (C++ ./run o Octave)" })

-- Runner definitivo para Kato (Integrado con direnv)
local function smart_run_project()
  -- 1. Guarda el archivo antes de correr
  vim.cmd("silent! write")

  local ft = vim.bo.filetype

  -- Caso especial para LaTeX: usa el compilador continuo de VimTeX
  if ft == "tex" then
    vim.cmd("VimtexCompile")
    return
  end

  local command = ""
  local has_pom = vim.fn.filereadable(vim.fn.getcwd() .. "/pom.xml") == 1

  if ft == "java" or has_pom then
    command = "./mvnw spring-boot:run"
  elseif ft == "cpp" then
    command = "./run"
  elseif ft == "octave" or ft == "matlab" then
    command = vim.fn.expand("%:t:r")
  else
    vim.notify("No hay comando configurado para: " .. ft, vim.log.levels.WARN)
    return
  end

  -- 2. Ejecuta en la terminal flotante de ToggleTerm solo para los demás lenguajes
  vim.cmd('TermExec cmd="' .. command .. '" direction=float')
end

-- 3. El mapeo estrella: Ctrl + Enter
vim.keymap.set("n", "<C-CR>", smart_run_project, { desc = "Run project with direnv env" })

vim.api.nvim_create_user_command("JavaNew", function()
  local types = { "Class", "Exception", "Interface", "Record", "Enum" }

  -- 1. Despliega el menú para elegir el tipo
  vim.ui.select(types, { prompt = "Elige el tipo de archivo Java:" }, function(choice)
    if not choice then
      return
    end

    -- 2. Pide el nombre de la clase
    vim.ui.input({ prompt = "Nombre (" .. choice .. "): " }, function(name)
      if not name or name == "" then
        return
      end

      -- Obtiene la ruta del directorio actual (o la raíz del proyecto)
      local path = vim.fn.expand("%:p:h")
      if path == "" then
        path = vim.fn.getcwd()
      end
      local filepath = path .. "/" .. name .. ".java"

      -- Deduce el package para Spring Boot / Maven
      local package_name = ""
      local src_path = "src/main/java/"
      local src_index = path:find(src_path, 1, true)
      if src_index then
        package_name = path:sub(src_index + string.len(src_path)):gsub("/", ".")
      end

      -- 3. Construye la plantilla según lo elegido
      local lines = {}
      if package_name ~= "" then
        table.insert(lines, "package " .. package_name .. ";")
        table.insert(lines, "")
      end

      if choice == "Exception" then
        table.insert(lines, "public class " .. name .. " extends RuntimeException {")
        table.insert(lines, "    public " .. name .. "(String message) {")
        table.insert(lines, "        super(message);")
        table.insert(lines, "    }")
        table.insert(lines, "}")
      elseif choice == "Interface" then
        table.insert(lines, "public interface " .. name .. " {")
        table.insert(lines, "")
        table.insert(lines, "}")
      elseif choice == "Record" then
        table.insert(lines, "public record " .. name .. "() {")
        table.insert(lines, "}")
      elseif choice == "Enum" then
        table.insert(lines, "public enum " .. name .. " {")
        table.insert(lines, "")
        table.insert(lines, "}")
      else -- Class por defecto
        table.insert(lines, "public class " .. name .. " {")
        table.insert(lines, "")
        table.insert(lines, "}")
      end

      -- 4. Abre el nuevo archivo, inserta el texto y guarda
      vim.cmd("edit " .. vim.fn.fnameescape(filepath))
      local buf = vim.api.nvim_get_current_buf()
      vim.api.nvim_buf_set_lines(buf, 0, -1, false, lines)
      vim.cmd("write")

      -- Sitúa el cursor en la posición ideal (dentro de las llaves)
      local cursor_line = #lines - 1
      if choice == "Exception" then
        cursor_line = #lines
      end
      pcall(vim.api.nvim_win_set_cursor, 0, { cursor_line, 4 })
    end)
  end)
end, {})

-- Atajo de teclado: <leader>cj (Code Java)
vim.keymap.set("n", "<leader>cj", ":JavaNew<CR>", { desc = "Crear archivo Java (Menú)" })
