Param(
    [string]$folder,
    [string]$result,
    [string]$filter,
    [string]$rule,
    [bool]$one_file = $false
    )

if($result -eq "")
{
    $result = "bin/";
}

if($folder -eq "")
{
    echo "folder non specifier";
    echo "-folder";
    echo "-result";
    echo "-filter";
    echo "-rule";
    exit;
}

if(($filter -eq "")-and($rule -eq ""))
{
    echo "filter or rule non specifier";
    echo "-folder";
    echo "-result";
    echo "-filter";
    echo "-rule";
    exit;
}

if ($one_file -eq $false) {
    mkdir $result$folder;
}

$ls_result = dir $folder;
$files = New-Object System.Collections.ArrayList;
foreach($ls_element in $ls_result)
{
    $is_valide = $false;
    for($t = 0; $t -lt $ls_element.length;$t++)
    {
        if($ls_element.Name[$t] -eq '.')
        {
            $is_valide = $true;
        }
    }
    if($is_valide -eq $true)
    {
        $files.Add($ls_element);
    }
}
if ($rule -ne "") {
    $rules_file = $rule;
}
else {
    $rules_file = Get-Content -Path $filter -Delimiter false;
}

$rules = $rules_file.Split('@');

$replace = New-Object System.Collections.ArrayList;
for($i = 0; $i -lt $rules.length; $i = $i + 2)
{
    $replace += "-replace '"+ $rules[$i] +"', '"+ $rules[$i+1] +"'";
}
echo "regle charge";

foreach($file in $files)
{
    Write-Host $file.name -NoNewLine;
    $file_name = $file.name;
    if ($one_file) {
        powershell -Command "(gc $folder) $replace | Out-File -encoding ASCII $result$file_name";        
    }
    else {
        powershell -Command "(gc $folder$file_name) $replace | Out-File -encoding ASCII $result$folder$file_name";
    }
    echo " fait";
}
echo "fin";