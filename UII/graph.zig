const std = @import("std");

// pub const PairIntFloat = struct {
//     x: u32,
//     y: f32,
// };

pub const Edge = struct {
    from: u32,
    weight: f32,
    to: u32,
};


// only integers with floats as weight for a while..
// should i just put things around it cause a modules just a struct? 
pub const Graph = struct {
    data: std.AutoHashMap(u32, std.ArrayList(Edge)),
    is_directed: bool,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator, is_directed: bool, triples: []const Edge) !Graph {
        var graph = Graph{
            .data = std.AutoHashMap(u32, 
                std.ArrayList(Edge)).init(allocator),
            .is_directed = is_directed,
            .allocator = allocator,
        };

        errdefer graph.data.deinit();
        for (triples) |edge| {
            try graph.addEdge(edge);

            if (!is_directed) {
                try graph.addEdge(.{.from = edge.to, .weight = edge.weight, .to = edge.from});
            }
        }

        return graph;
    }

    fn addEdge(self: *Graph, edge: Edge) !void {
        const res = try self.data.getOrPut(edge.from);

        if (!res.found_existing) {
            res.value_ptr.* = std.ArrayList(Edge).init(self.allocator);
        }

        try res.value_ptr.append(edge);
    }

    fn addNode(self: *Graph, node: u32) !void {
        const res = try self.data.getOrPut(node);

        if (!res.found_existing) {
            res.value_ptr.* = std.ArrayList(Edge).init(self.allocator);
        }
    }

    // u pick the first vertice. Whatever..
    // Only for non-directed?
    // IF THE GRAPH IS NOT CONEXE OR EMPTY, THIS WILL BE CRAZY!
    pub fn prim(self: Graph, V: u32) !Graph {
        var T = std.ArrayList(Edge).init(self.allocator);
        defer T.deinit();
        var Z = std.AutoArrayHashMap(u32, void).init(self.allocator);
        defer Z.deinit();

        try Z.put(V, {});
        // The N's just the !Z

        const NUM_KEYS = self.data.count();
        while (Z.count() < NUM_KEYS) {
            // const KEYS = std.AutoArrayHashMap(i32, void).init(self.allocator);
            const MIN_VERTICE: Edge = find_min: {
                var min = std.math.inf(f32);
                var min_orange: Edge = undefined;
                for (Z.keys()) |green| { // greens are the visited vertexes
                    const from_green_edges = self.data.get(green).?;
                    for (from_green_edges.items) |orange| { // oranges are the edges
                        if (!Z.contains(orange.to) and orange.weight < min) { 
                            min = orange.weight; 
                            min_orange = orange;
                        }
                    }
                }

                break :find_min min_orange;
            };

            try Z.put(MIN_VERTICE.to, {});
            try T.append(MIN_VERTICE);

        }

        // assuming thats only for non directed graphs
        return Graph.init(self.allocator, false, T.items);

    }
};
