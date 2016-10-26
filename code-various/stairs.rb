# include standard API hooks.
      require 'sketchup.rb'

# Ruby Console - debug
  Sketchup.send_action "showRubyPanel:"

# draw stairs added as menu item
UI.menu("PlugIns").add_item("Draw stairs")  { 
   UI.messagebox("Stairs about to be drawn.")
  draw_stairs 
}
  
 def draw_stairs  
   stairs = 10  
   rise = 8  
   run = 12  
   width = 100  
   thickness = 3
      
 # Get handles to our model and the Entities collection it contains. 
   model = Sketchup.active_model  
   entities = model.entities 

   for step in 1..stairs      
     # calculate stair corners   
         x1 = 0 
         x2 = width  
         y1 = run * step 
         y2 = run * (step + 1)  
         z = rise * step      

     # points based on corners
        pt1 = [x1, y1, z]    
        pt2 = [x2, y1, z]    
        pt3 = [x2, y2, z]    
        pt4 = [x1, y2, z]   

     # to make face, call method on entities collection  
     new_face = entities.add_face pt1, pt2, pt3, pt4 
     # raise face on Z axis (height) 
     new_face.pushpull thickness 
    end

end