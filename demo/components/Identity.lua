local IdentityComponent = class('Identity')

function IdentityComponent:initialize(t)
    self.name = t.name
    self.isPlayer = t.isPlayer or false
end

return IdentityComponent