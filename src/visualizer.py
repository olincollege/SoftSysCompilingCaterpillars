
import networkx as nx
from networkx.drawing.nx_agraph import write_dot, graphviz_layout
import matplotlib.pyplot as plt

tree_file = open("output.txt", 'r')
lines = tree_file.readlines()

graph = nx.DiGraph()
sl_iter = 1
s_iter = 1
w_iter = 1
if_iter = 1
cond_iter = 1
exp_iter = 1
oper_iter = 1
comp_iter = 1
value_iter = 1
var_iter = 1
e_iter = 1
graph.add_node(f"Statement List {sl_iter}")
sl_iter += 1

operator_map = {
    "0": "+",
    "1": "-",
    "2": "*",
    "3": "/",
}

comp_map = {
    "0": "=",
    "1": "<",
    "2": ">",
    "3": "!"
}
def create_new_list(graph, parent_node, lines):
    global sl_iter
    global s_iter
    global w_iter
    global if_iter 
    global cond_iter
    global exp_iter 
    global oper_iter
    global comp_iter
    global value_iter
    global var_iter
    if not lines:
        return
    node = f"Statement List {sl_iter}"
    sl_iter += 1
    graph.add_node(node)
    graph.add_edge(parent_node, node)
    parent_node = node
    tokens = lines[0].split()
    if tokens[0] == "endwhile" or tokens[0] == "endif":
        graph.remove_node(node)
        del lines[0]
        return
    if tokens[0] == "else":
        print(f"else lines {lines}")
        return
    if tokens[0] == "while":
        create_while(graph, parent_node, lines)
        create_new_list(graph, parent_node, lines)
    elif tokens[0] == "if":
        create_if(graph, parent_node, lines)
        create_new_list(graph, parent_node, lines)
    else:
        create_statement(graph, parent_node, lines[0].split())
        del lines[0]
        create_new_list(graph, parent_node, lines)

        

def create_statement(graph, parent_node, tokens):
    global sl_iter
    global s_iter
    global w_iter
    global if_iter 
    global cond_iter
    global exp_iter 
    global oper_iter
    global comp_iter
    global value_iter
    global var_iter
    if tokens[0] == 'done':
        graph.remove_node(parent_node)
        return
    node = f"Statement {s_iter}"
    s_iter += 1
    graph.add_node(node)
    graph.add_edge(parent_node, node)
    parent_node = node
    node = f"Variable {var_iter}\n {tokens[2]}"
    var_iter += 1
    graph.add_edge(parent_node, node)
    print(tokens[3:])
    create_expression(graph, parent_node, tokens[3:])
    

def create_expression(graph, parent_node, tokens):
    global sl_iter
    global s_iter
    global w_iter
    global if_iter 
    global cond_iter
    global exp_iter 
    global oper_iter
    global comp_iter
    global value_iter
    global var_iter
    i = 0
    while i < len(tokens):
        if i % 2 == 0:
            node = f"Expression {exp_iter}"
            exp_iter += 1
            graph.add_edge(parent_node, node)
            parent_node = node
            node = f"Value {value_iter}\n {tokens[i]}"
            value_iter += 1
            graph.add_node(node)
            graph.add_edge(parent_node, node)
        else:
            node = f"Operator {oper_iter}\n {operator_map[tokens[i]]}"
            oper_iter += 1
            graph.add_node(node)
            graph.add_edge(parent_node, node)
        i += 1

def create_conditional(graph, parent_node, line):
    global sl_iter
    global s_iter
    global w_iter
    global if_iter 
    global cond_iter
    global exp_iter 
    global oper_iter
    global comp_iter
    global value_iter
    global var_iter
    node = f"Conditional {cond_iter}"
    cond_iter += 1
    graph.add_node(node)
    graph.add_edge(parent_node, node)
    parent_node = node
    if len(line.split(' 10 ')) > 1:
        comp = '='
        sides = line.split(' 10 ')
    elif len(line.split(' 11 ')) > 1:
        comp = '<'
        sides = line.split(' 11 ')
    elif len(line.split(' 12 ')) > 1:
        comp = '>'
        sides = line.split(' 12 ')
    else:
        comp = '!'
        sides = line.split(' 13 ')
    print(f"sides: {sides}")
    create_expression(graph, parent_node, sides[0].split())
    node = f"Comparator {comp_iter} \n {comp}"
    comp_iter += 1
    graph.add_node(node)
    graph.add_edge(parent_node, node)
    create_expression(graph, parent_node, sides[1].split())

def create_while(graph, parent_node, lines):
    global sl_iter
    global s_iter
    global w_iter
    global if_iter 
    global cond_iter
    global exp_iter 
    global oper_iter
    global comp_iter
    global value_iter
    global var_iter
    node = f"While {w_iter}"
    w_iter += 1
    graph.add_node(node)
    graph.add_edge(parent_node, node)
    parent_node = node
    comp_line = ' '.join(lines[0].split()[2:])
    create_conditional(graph, parent_node, comp_line)
    del lines[0]
    create_new_list(graph, parent_node, lines)


def create_if(graph, parent_node, lines):
    global sl_iter
    global s_iter
    global w_iter
    global if_iter 
    global cond_iter
    global exp_iter 
    global oper_iter
    global comp_iter
    global value_iter
    global var_iter
    global e_iter
    node = f"Branch {if_iter}"
    graph.add_node(node)
    graph.add_edge(parent_node, node)
    parent_node = node
    if lines[0][0:2] == "if":
        node = f"If {if_iter}"
        if_iter += 1
        comp_line = ' '.join(lines[0].split()[2:])
        graph.add_node(node)
        graph.add_edge(parent_node, node)
        create_conditional(graph, node, comp_line)
        del lines[0]
        create_new_list(graph, parent_node, lines)
        print(f"if lines {lines}")
    if not lines:
        return
    if lines[0][0:4] == "else":
        node = f"Else {e_iter}"
        e_iter += 1
        graph.add_node(node)
        graph.add_edge(parent_node, node)
        del lines[0]
        create_new_list(graph, node, lines)

parent_node = "Statement List 1"
create_new_list(graph, parent_node, lines)
plt.figure(figsize=(100, 50))
plt.title('draw_networkx')
pos = graphviz_layout(graph, prog='dot')
nx.draw_networkx(graph, pos, arrows=True, node_color="white")
plt.savefig('nx_test.png')


