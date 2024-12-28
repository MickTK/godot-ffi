extends Control
class_name Main

func exit(secs:float = 0.25) -> void:
	await get_tree().create_timer(secs).timeout
	get_tree().quit()


func _ready() -> void:
	print("Hello world!")
	
	var o := Object.new()
	
	
	
	
	exit()
