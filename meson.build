project('treecount', 'c',
	default_options : [
	'c_std=c11',
	'warning_level=3',
	'b_lundef=false',
	'b_sanitize=address,undefined'])

src = [ 'src/count.c' ]

executable('count',
	   sources : src)

run_target('inspector',
	   command : 'scripts/inspect.sh')
