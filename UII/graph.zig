const std = @import("std");

pub const PairIntFloat = struct {
    x: u32,
    y: f32,
};

pub const Edge = struct {
    from: u32,
    weight: f32,
    to: u32,
};

// only integers with floats as weight for a while..
pub const Graph = struct {
    data: std.AutoHashMap(u32, std.ArrayList(PairIntFloat)),
    is_directed: bool,
    allocator: std.mem.Allocator,

    pub fn init(allocator: std.mem.Allocator, is_directed: bool, triples: []const Edge) !Graph {
        var graph = Graph{
            .data = std.AutoHashMap(u32, PairIntFloat).init(allocator),
            .is_directed = is_directed,
            .allocatgor = allocator,
        };

        errdefer graph.data.deinit();
        for (triples) |edge| {
            try graph.addEdge(edge.from, edge.to, edge.weight);
            // try graph.data.put(edge.from, .{ .x = edge.to, .y = edge.weight });

            if (!is_directed) {
                try graph.addEdge(edge.to, edge.from, edge.weight);
            }
        }

        return graph;
    }

    fn addEdge(self: *Graph, from: u32, to: u32, weight: f32) !void {
        const res = try self.data.getOrPut(from);

        if (!res.found_existing) {
            res.value_ptr.* = std.ArrayList(PairIntFloat).init(self.allocator);
        }

        try res.value_ptr.append(.{ .x = to, .y = weight });
    }

    // u pick the first vertice. Whatever..
    pub fn prim(self: Graph, V: u32) Graph {
        var Z = std.AutoHashMap(i32, void).init(self.allocator);
        defer self.deinit();

        Z.put(V, {});

        // The N's just the !Z

        const NUM_KEYS = self.data.count();
        while (Z < NUM_KEYS) {
            // const KEYS = std.AutoArrayHashMap(i32, void).init(self.allocator);
            const MIN_VERTICE = find_min: {
                var min = std.math.inf(f32);
                for (Z.keys()) |green| {
                    for (self.data.get(green)) |orange| {
                        if (!Z.contains(orange.x) and orange.y < min) min = orange.y;
                    }
                }

                break :find_min min;
            };

            for (self.data.keys()) |from| {
                if (!Z.contains(from)) continue;







                
            }
        }
    }
};
