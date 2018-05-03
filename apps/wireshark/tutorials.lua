-- create a new dissector
local tcp_proto = Proto( "tcp_proto", "TCP" )

-- create the protocol fields
tcp_proto.fields.symbol = ProtoField.uint32( 'tcp_proto.symbol', "Symbol", base.HEX )
tcp_proto.fields.length = ProtoField.uint32( 'tcp_proto.length', "Length", base.DEC )
tcp_proto.fields.content = ProtoField.string( 'tcp_proto.content', "Content" )

-- the dissector function
function tcp_proto.dissector( tvbuf, pinfo, tree )
    -- adding fields to the tree
    local subtree = tree:add( tcp_proto, tvbuf, "TCP" )
    local offset = 0
    subtree.add( tcp_proto.fields.symbol, tvbuf( 0, 4 ) ) -- a unque symbol
    subtree.add( tcp_proto.fields.length, tvbuf( 4, 8 ) ) -- a length field in 4 bytes
    subtree.add( tcp_proto.fields.content, tvbuf( 12, len ) ) -- content as long as length
end

-- -- register the dissector
-- local tcp_port_table = DissectorTable.get( "tcp.port" )
-- tcp_port_table:add( 6969, tcp_proto.dissector )

-- heuristic function to resolve problem with non-predictable set of ports
function heur_tcp_prot_fun( tvbuf, pinfo, tree )
    if tvbuf(0,4):uint() == 100 then
      tcp_proto.dissector( tvbuf, pinfo, tree )
      return true
    end
    return false
end

--register heuristic function with protocol
tcp_proto:register_heuristic( "tcp", heur_tcp_prot_fun )

-- examples from another tutorial
-- -- a initialization routine
-- local packet_counter
-- function MYPROTO.init ()
--     packet_counter = 0
-- end

-- -- add a integer preference
-- local p = MYPROTO.prefs
-- p.value = Pref.uint( "Value", 0, "Start value for counting" )

-- -- use the preference
-- if not pinfo.visited and msgid:uint() >= p.value then
--     packet_counter = packet_counter + 1
-- end

-- -- add a enum preference 
-- local p = MYPROTO.prefs
-- local eval_enum = { 
--     { "First", "First value", 0 },
--     { "Second", "Second value", 1 },
--     { "Third", "Third value", 2 }
-- }

-- p.value = Pref.uint( "Value", 0, "Start value for counting" )
-- p.eval = Pref.enum( "Enum value", 1, "Another value", eval_enum, true )
-- p.text = Pref.statictext ( "The enum value is not yet implemented" )


