import pstats
p = pstats.Stats('raw')
p.strip_dirs().sort_stats(-1).print_stats()

