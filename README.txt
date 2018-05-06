ICP 2017/2018 Project - BLOCKEDITOR

Authors: Tomáš Pazdiora (xpazdi02)
         Michal Pospíšil (xpospi95)
		 
FEAUTURES OF THIS IMPLEMENTATION:
- Design patterns usage
-- Abstract Factories to generate specific block and port types
-- Decorator pattern to bond GUI and core functionality and more
-- Observer to update block values (using callbacks for specific computations) and more

- Intuitive user interface
-- We created an easy-to-use user interface with toolbars. We also support keyboard shortcuts
   and before closing the file, app will ask the user about saving changes 
   if the file was modified.
   
- Merge functionality
-- Merging is a feature that opens a file and merges it into the currently opened file.

- File format
-- We used the gph file format to avoid confusion with other file formats and ensuring
   that our app will not crash after attempting to open other filetypes.
   
- Help dialog
-- We created a help dialog to let the user know how to use the app.
   
DEFICIENCES OF THIS IMPLEMENTATION
- Saving values is not supported
-- Values in input and output blocks are not saved. Files will need to be filled with values 
   and recomputed again.
   
EXAMPLES
- sin(x) approximation.gph
-- Approxiamtion of sin(x) where x is in <0, pi>. First upper value is x and second bottom 
   value is a constant 0.05.