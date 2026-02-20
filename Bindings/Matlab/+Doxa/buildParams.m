function params = buildParams(options)
%BUILDPARAMS Convert name-value options to a parameter struct for MEX.
%   Internal utility. Strips empty fields before passing to the MEX layer.

    params = struct();
    fields = fieldnames(options);
    for i = 1:numel(fields)
        value = options.(fields{i});
        if ~isempty(value)
            params.(fields{i}) = value;
        end
    end
end
