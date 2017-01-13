
# this script cretaes a sierpinski pyramid (out of cubes, instead of pyramids)

# source: https://www.youtube.com/watch?v=uWvIdWBsv2Y

import bpy

# initial length of the object
length = 2

# function to remove doubles
def removeDoubles():
    bpy.ops.object.editmode_toggle()
    bpy.ops.mesh.select_all(action='TOGGLE')
    bpy.ops.mesh.remove_doubles()
    bpy.ops.mesh.select_all(action='TOGGLE')
    bpy.ops.object.editmode_toggle()


# creates a group of 5 elements
def createGroup(length):
    
    # recursion end when the length is greater than 32
    if length < 33:
        bpy.ops.object.duplicate_move(OBJECT_OT_duplicate={"mode":'TRANSLATION'}, TRANSFORM_OT_translate={"value":(0, 0, -length)})
        bpy.ops.transform.translate(value=((length/2), 0, 0))
        bpy.ops.transform.translate(value=(0, (length/2), 0))
        bpy.ops.object.duplicate_move(OBJECT_OT_duplicate={"mode":'TRANSLATION'}, TRANSFORM_OT_translate={"value":(0, -length, 0)})
        bpy.ops.object.duplicate_move(OBJECT_OT_duplicate={"mode":'TRANSLATION'}, TRANSFORM_OT_translate={"value":(-length, 0, 0)})
        bpy.ops.object.duplicate_move(OBJECT_OT_duplicate={"mode":'TRANSLATION'}, TRANSFORM_OT_translate={"value":(0, length, 0)})
        bpy.ops.object.select_by_type(type='MESH')
        bpy.ops.object.join()
        removeDoubles()
        length = length * 2
        
        # function calls itself and creates another 5 elements
        length = createGroup(length)
    return length

if __name__ == "__main__":
    createGroup(length)
